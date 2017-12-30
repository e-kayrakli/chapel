import re
import itertools as it
import numpy as np

class chpl_range(object):
    def __init__(self, low, high, stride=1):
        self.low = low
        self.high = high
        self.stride = stride
    
    def __str__(self):
        if self.stride == 1:
            return '{}..{}'.format(self.low, self.high)
        else:
            return '{}..{} by {}'.format(self.low,
                                         self.high,
                                         self.stride)

    def __iter__(self):
        for i in range(self.low, self.high+1, self.stride):
            yield i

    def shape(self):
        return (self.low, self.high)
    
    def size(self):
        if self.stride != 1:
            print('ERROR: Strided range.size not implemented')
        return self.high-self.low+1


    def member(self, index):
        if not isinstance(index, int):
            print('ERROR: Arg to range.member must be int')
            
        if self.stride != 1:
            print('ERROR: Strided domain.member not implemented')

        return index >= self.low and index <= self.high

class chpl_domain(object):
    def __init__(self, ranges):
        self.strided = False
        self.ranges = []
        for r in ranges:
            if r.stride != 1:
                self.strided = True
            self.ranges.append(r)
        self.rank = len(ranges)

    # returns (xlimits, ylimits)
    def to_limit_tuple(self):
        # print('called ' + int(self.rank))
        if self.rank == 1 :
            return ( self.ranges[0].shape(), )
        elif self.rank == 2:
            return ( self.ranges[1].shape(),
                     self.ranges[0].shape() )

    def __str__(self):
        s = '{'
        s += str(self.ranges[0])
        for r in self.ranges[1:]:
            s += ', ' + str(r)
        s += '}'
        return s

    def __iter__(self):
        if len(self.ranges) == 1:
            for i in self.ranges[0]:
                yield i
        if len(self.ranges) == 2:
            for i,j in it.product(self.ranges[0],
                                  self.ranges[1]):
                yield (i,j)

    def is_positive(self):
        for r in self.ranges:
            if r.low < 0 or r.high < 0:
                return False
        return True

    def __getitem__(self, key):
        return self.ranges[key]

    def member(self, index):
        if len(index) != len(self.ranges):
            print("ERROR: Rank mismatch")

        
        for (i,r) in zip(index, self.ranges):
            if not r.member(i):
                return False

        return True

    def size(self):
        if self.strided is True:
            print('ERROR: domain.size for strided domains is not impl')

        size = 1
        for r in self.ranges:
            size *= r.size()
        return size

def range_from_shape(shape):
    
    return chpl_range(shape[0], shape[1])
        
class LogHandler(object):

    def __init__(self, rank):

        ## init helpers
        def __gen_csv_pattern(start, item, end, count=-1):
            if count == -1:
                count = self.rank
            pattern = r"^" + start
            pattern += item
            for r in range(count-1):
                pattern += ", " + item
            pattern += end+'$'
            return pattern

        def __gen_idx_pattern(rank):
            return __gen_csv_pattern(
                    start='\(',
                    item ='([0-9]+)',
                    end  ='\)')

        def __gen_dom_pattern(rank):
            return __gen_csv_pattern(
                    start='\{',
                    item ='([0-9]+)\.\.([0-9]+)( by [0-9]+)?',
                    end  ='\}')

        self.rank = rank
        self.domain_pattern = __gen_dom_pattern(self.rank)
        self.index_pattern = __gen_idx_pattern(self.rank)
    # endof init

    def generate_domain(self, limit_tuple):
        if self.rank == 1 :
            return chpl_domain([range_from_shape(limit_tuple[0])])
        elif self.rank == 2:
            return chpl_domain([range_from_shape(limit_tuple[1]),
                                range_from_shape(limit_tuple[0])])


    def get_dom(self, line):

        def dom_from_mg(match_groups):
            # match group must have multiple-of-3 ints
            mgr_len = len(match_groups)
            if mgr_len % 3 != 0:
                print('Wrong match group length {}'.format(mgr_len))

            rank = int(mgr_len/3)
            ranges = []
            for r in range(rank):
                base = r*3
                if match_groups[base+2] == None:
                    stride = 1
                else:
                    stride = match_groups[base+2].split()[-1]

                ranges.append(chpl_range(int(match_groups[base]),
                                         int(match_groups[base+1]),
                                         int(stride)))
            return chpl_domain(ranges)

        match = re.match(self.domain_pattern, line)
        if match:
            return dom_from_mg(match.groups())
        else:
            return None

    # TODO maybe change to get_tuple ?
    def get_index(self, line):
        match = re.match(self.index_pattern, line)
        if match:
            if self.rank == 1:
                return (int(match.group(1)), )
            elif self.rank == 2:
                return (int(match.group(1)), int(match.group(2)))
        else:
            print('Invalid index : ', line) 

class MetaLog(object):

    def __init__(self, filename):
        with open(filename) as f:
            # self.rank = get_rank(f.readline())
            self.rank = int(f.readline())
            self.__lh = LogHandler(self.rank)
            self.target_loc_shape = self.__lh.get_index(f.readline())

class LocaleLog(object):

    # TODO rank needs to go
    def __init__(self, filename, rank, debug=False):

        self.__lh = LogHandler(rank)

        with open(filename) as f:
            whole = self.__lh.get_dom(f.readline())

            # now start reading subdomain(s). At this point we do not know
            # how many there are, so we do some regexp checking for each
            # line we read to determine whether it is a domain or an index
            subdoms = []
            tmp_line = f.readline()
            dom = self.__lh.get_dom(tmp_line)

            while dom != None:
                subdoms.append(dom)
                last_pos = f.tell()
                tmp_line = f.readline()
                dom = self.__lh.get_dom(tmp_line)

            # revert back to the last domain position so as not to miss the
            # first index
            f.seek(last_pos)

            d1_offset = whole[0].low
            if rank == 2:
                d2_offset = whole[1].low

            access_mat_d1_size = whole[0].high-whole[0].low+1
            if rank == 1:
                access_mat_d2_size = 1
            elif rank == 2:
                access_mat_d2_size = whole[1].high-whole[1].low+1

            # TODO we probably want to use an ndarray here to be able to
            # cover multidimensional data in a sane way
            access_mat = [[0 for x in range(access_mat_d2_size)] for y in
                    range(access_mat_d1_size)]

            if debug:
                print_access_mat(access_mat)
                print()

            max_access = 0
            for line in f:
                real_index = self.__lh.get_index(line)
                if rank == 1:
                    index = (real_index[0]-d1_offset, 0)
                elif rank == 2:
                    index = (real_index[0]-d1_offset, real_index[1]-d2_offset)
                access_mat[index[0]][index[1]] += 1
                if access_mat[index[0]][index[1]] > max_access:
                    max_access = access_mat[index[0]][index[1]] 

            if debug:
                print_access_mat(access_mat)

        # TODO fix this
        self.rank = rank
        self.whole = whole
        self.subdoms = subdoms
        self.access_mat = access_mat
        self.max_access = max_access

    def gen_rar(self):
        num_loc = 0
        num_rem = 0
        for idx,acc_cnt in self.iter_idx_acc_cnt():
            tmp_loc = False
            for d in self.subdoms:
                if d.member(idx):
                    tmp_loc = True

            if tmp_loc:
                num_loc += acc_cnt
            else:
                num_rem += acc_cnt

        return float(num_rem)/(num_loc+num_rem)

    def get_num_loc_idxs(self):
        return sum([d.size() for d in self.subdoms])

    def gen_access_mem_ratio(self):
        num_rem = 0
        for idx,acc_cnt in self.iter_idx_acc_cnt():
            if acc_cnt == 0:
                continue

            tmp_loc = False
            for d in self.subdoms:
                if d.member(idx):
                    tmp_loc = True

            if not tmp_loc:
                num_rem += 1

        return float(num_rem)/self.get_num_loc_idxs()

    def iter_idx_acc_cnt(self):
        if self.rank == 1:
            for (idx, acc_cnt) in enumerate(self.access_mat):
                yield ((idx,), acc_cnt[0])

        elif self.rank == 2:
            for (i, acc_cnts) in enumerate(self.access_mat):
                for (j, acc_cnt) in enumerate(acc_cnts):
                    yield ((i,j),acc_cnt)

        else:
            print('ERROR: cannot iterate rank>2 yet')

    def gen_access_bbox(self):
        if self.rank == 1:
            min_idx = -1  # only to mark that it hasn't been found yet
            max_idx = -1  # only to mark that it hasn't been found yet
            for (idx, acc_cnt) in enumerate(self.access_mat):
                if acc_cnt[0] > 0 and min_idx == -1:
                    min_idx = idx
                if acc_cnt[0] > 0 and idx > max_idx:
                    max_idx = idx
            return chpl_domain([chpl_range(min_idx, max_idx)])
        elif self.rank == 2:
            l,t,r,b = -1, -1, -1, -1
            for (i, acc_cnts) in enumerate(self.access_mat):
                for (j, acc_cnt) in enumerate(acc_cnts):
                    if acc_cnt > 0:
                        if t == -1:
                            t = i
                        b = i
                        if l == -1 or l > j:
                            l = j
                        if r < j:
                            r = j
            return chpl_domain([chpl_range(t, b), chpl_range(l, r)])

    def gen_access_bbox_efficiency(self):
        bbox = self.gen_access_bbox()

        accessed = 0
        if self.rank == 1:
            for idx in bbox:
                if self.access_mat[idx][0] > 0:
                    accessed += 1
        elif self.rank == 2:
            for i,j in bbox:
                if self.access_mat[i][j] > 0:
                    accessed += 1

        return float(accessed)/bbox.size()
            

    def gen_pairwise_access_bbox(self, llhs):
        if self.rank == 1:
            self.pwise_bboxes = []
            for ll in llhs:
                min_idx = -1  # only to mark that it hasn't been found yet
                max_idx = -1  # only to mark that it hasn't been found yet
                for subdom in ll.subdoms:
                    for i in subdom:
                        if self.access_mat[i][0] > 0 and min_idx == -1:
                            min_idx = i
                        if self.access_mat[i][0] > 0 and i > max_idx:
                            max_idx = i
                self.pwise_bboxes.append(chpl_domain([chpl_range(min_idx,
                    max_idx)]))
            return self.pwise_bboxes
        elif self.rank == 2:
            self.pwise_bboxes = []
            for ll in llhs:
                l, t, r, b = -1, -1, -1, -1
                for subdom in ll.subdoms:
                    for i,j in subdom:
                        if self.access_mat[i][j] > 0:
                            if t == -1:
                                t = i
                            b = i
                            if l == -1 or l > j:
                                l = j
                            if r < j:
                                r = j

                new_dom = chpl_domain([chpl_range(t, b),
                                       chpl_range(l, r)])

                self.pwise_bboxes.append(new_dom)

            return self.pwise_bboxes


    def print_access_mat(self, mat):
        for i in range(len(mat)):
            print(mat[i])
