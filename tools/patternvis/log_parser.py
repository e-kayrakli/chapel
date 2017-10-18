import re
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

    def shape(self):
        return (self.low, self.high)

class chpl_domain(object):
    def __init__(self, ranges):
        self.ranges = []
        for r in ranges:
            self.ranges.append(r)


    def __str__(self):
        s = '{'
        s += str(self.ranges[0])
        for r in self.ranges[1:]:
            s += ', ' + str(r)
        s += '}'
        return s

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

    # returns (xlimits, ylimits)
    def generate_limit_tuple(self, dom):
        # print('called ' + int(self.rank))
        if self.rank == 1 :
            return ( dom.ranges[0].shape(), )
        elif self.rank == 2:
            return ( dom.ranges[1].shape(),
                     dom.ranges[0].shape() )

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
            return self.generate_limit_tuple(dom_from_mg(match.groups()))
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
            whole_lims = self.__lh.get_dom(f.readline())

            # now start reading subdomain(s). At this point we do not know
            # how many there are, so we do some regexp checking for each
            # line we read to determine whether it is a domain or an index
            subdom_lims = []
            tmp_line = f.readline()
            dom = self.__lh.get_dom(tmp_line)

            while dom != None:
                subdom_lims.append(dom)
                last_pos = f.tell()
                tmp_line = f.readline()
                dom = self.__lh.get_dom(tmp_line)

            # revert back to the last domain position so as not to miss the
            # first index
            f.seek(last_pos)

            d1_offset = whole_lims[0][0]
            if rank == 2:
                d2_offset = whole_lims[1][0]

            access_mat_d1_size = whole_lims[0][1]-whole_lims[0][0]+1
            if rank == 1:
                access_mat_d2_size = 1
            elif rank == 2:
                access_mat_d2_size = whole_lims[1][1]-whole_lims[1][0]+1

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
        self.whole_lims = whole_lims
        self.subdom_lims = subdom_lims
        self.access_mat = access_mat
        self.max_access = max_access

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

    def print_access_mat(self, mat):
        for i in range(len(mat)):
            print(mat[i])
