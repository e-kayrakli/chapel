import re
import math
import itertools as it
from pathlib import Path
import lz4.frame

# simple wrapper around numpy or python multid arrays/lists
class AccessMat(object):

    def __init__(self, shape, no_numpy):
        self.shape = shape
        self.ndims = len(shape)

        self.no_numpy = no_numpy

        if self.no_numpy:
            if self.ndims == 1:
                self.__mat = [0 for i in range(self.shape[0])]
            elif self.ndims == 2:
                self.__mat = [0 for i in range(self.shape[0]) for j in
                        range(self.shape[1])]
            else:
                print(self.ndims, ' dimensional arrays are only supported via numpy')
                assert False
        else:
            import numpy as np
            self.__mat = np.zeros(self.shape)

    def __getitem__(self, idx):

        if self.no_numpy:
            if isinstance(idx, int):
                assert self.ndims == 1

                return self.__mat[idx]
            elif isinstance(idx, tuple):
                assert len(idx) == self.ndims

                if self.ndims == 1:
                    return self.__mat[idx[0]]
                else:  # must be 2
                    assert self.ndims == 2

                    return self.__mat[idx[0]*self.shape[1]+idx[1]]
        else:
            return self.__mat[idx]

    def __setitem__(self, idx, value):

        if self.no_numpy:
            if isinstance(idx, int):
                assert self.ndims == 1

                self.__mat[idx] = value
            elif isinstance(idx, tuple):
                assert len(idx) == self.ndims

                if self.ndims == 1:
                    self.__mat[idx[0]] = value
                else:  # must be 2
                    assert self.ndims == 2

                    self.__mat[idx[0]*self.shape[1]+idx[1]] = value
        else:
            self.__mat[idx] = value

    def enum(self):
        if self.no_numpy:
            if self.ndims == 1:
                for idx, item in zip(range(self.shape[0]), self.__mat):
                    yield idx, item
            elif self.ndims == 2:
                for idx, item in zip(it.product(range(self.shape[0]),
                                                range(self.shape[1])),
                                     self.__mat):
                    yield idx, item
            else:
                assert False, 'invalid ndims'
        else:
            import numpy as np
            for idx, item in np.ndenumerate(self.__mat):
                yield idx, item


def init_log_handlers(meta_log_name, locale_log_prefix, no_numpy):
    if not no_numpy:
        import numpy as np

    metalog_handler = MetaLog(meta_log_name)

    target_loc_shape = metalog_handler.target_loc_shape
    if isinstance(target_loc_shape, int):
        target_loc_shape = (target_loc_shape, )

    rank = len(target_loc_shape)
    num_locs = 1
    for t in target_loc_shape:
        num_locs *= t

    lls = []
    for i in range(num_locs):
        lls.append(LocaleLog(filename=locale_log_prefix+str(i),
                             rank=metalog_handler.rank,
                             no_numpy=no_numpy))

    return (metalog_handler, lls)

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
        # I hate to do this but:
        if self.high == self.low and self.high == -1:
            return 0

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

    def __repr__(self):
        return self.__str__()

    def __iter__(self):
        for idx in it.product(*self.ranges):
            yield idx
        # if len(self.ranges) == 1:
            # for i in self.ranges[0]:
                # yield i
        # if len(self.ranges) == 2:
            # for i,j in it.product(self.ranges[0],
                                  # self.ranges[1]):
                # yield (i,j)

    def transpose(self):
        assert self.rank == 2
        return chpl_domain([self.ranges[1], self.ranges[0]])

    def tuple_for_training(self):
        return tuple(it.chain.from_iterable(
                        (r.low, r.high) for r in self.ranges)
                    )

    def is_positive(self):
        for r in self.ranges:
            if r.low < 0 or r.high < 0:
                return False
        return True

    def __getitem__(self, key):
        return self.ranges[key]

    def member(self, index):
        if isinstance(index, tuple):
            loc_index = index
        else:
            loc_index = (index, )

        if len(loc_index) != len(self.ranges):
            print("ERROR: Rank mismatch")

        
        for (i,r) in zip(loc_index, self.ranges):
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

    def is_empty(self):
        return self.size() == 0

    def shape(self):
        return tuple([r.size() for r in self.ranges])

    def bbox_expansion(self, index):
        loc_index = (index, ) if isinstance(index, int) else index

        if self.is_empty():
            return chpl_domain([chpl_range(i, i) for i in loc_index])

        new_ranges = []
        for i,r in zip(loc_index, self.ranges):
            new_ranges.append(chpl_range(low=r.low if r.low<i else i,
                                         high=r.high if r.high>i else i))

        return chpl_domain(new_ranges)

def range_from_shape(shape):
    return chpl_range(shape[0], shape[1])
        
def to_zero_based(index, domain):
    if isinstance(index, tuple):
        num = len(index)
        assert num == domain.rank
        loc_index = []

        # for tup_idx, idx in enumerate(index):
        for i,r in zip(index, domain.ranges):
            loc_index.append(i-r.low)

        return tuple(loc_index)
    else:
        assert domain.rank == 1
        return index - domain.ranges[0].low

def to_nonzero_based(index, domain):
    if isinstance(index, tuple):
        num = len(index)
        assert num == domain.rank
        loc_index = []

        # for tup_idx, idx in enumerate(index):
        for i,r in zip(index, domain.ranges):
            loc_index.append(i+r.low)

        return tuple(loc_index)
    else:
        assert domain.rank == 1
        return index + domain.ranges[0].low



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

        ## init helpers
        def __gen_ssv_pattern(start, item, end, count=-1):
            if count == -1:
                count = self.rank
            pattern = r"^" + start
            pattern += item
            for r in range(count-1):
                pattern += ' ' + item
            pattern += end+'$'
            return pattern

        def __gen_idx_pattern(rank):
            return __gen_csv_pattern(
                    start='\(',
                    item ='([0-9]+)',
                    end  ='\)')

        def __gen_comp_idx_pattern(rank):
            return __gen_ssv_pattern(
                    start='',
                    item ='([0-9]+)',
                    end  ='')

        def __gen_dom_pattern(rank):
            return __gen_csv_pattern(
                    start='\{',
                    item ='([0-9]+)\.\.([0-9]+)( by [0-9]+)?',
                    end  ='\}')

        self.rank = rank
        self.domain_pattern = __gen_dom_pattern(self.rank)
        self.index_pattern = __gen_idx_pattern(self.rank)
        self.comp_index_pattern = __gen_comp_idx_pattern(self.rank)
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
    def get_index(self, line, compressed=False):
        if compressed:
            match = re.match(self.comp_index_pattern, line)
        else:
            match = re.match(self.index_pattern, line)
        if match:
            if self.rank == 1:
                return (int(match.group(1)), )
            elif self.rank == 2:
                # t = match.groups()
                return (int(match.group(1)), int(match.group(2)))
                # return (int(t[0]), int(t[1]))
            else:
                return tuple(int(g) for g in match.groups())
        else:
            print('Invalid index : ', line) 

    def access_bbox(self, file_prefix):

        file_frmt = file_prefix+'_buf{}_dump{}.dom'
        buf_counter = 0


        dlows = [+math.inf for _ in range(self.rank)]
        dhighs = [-math.inf for _ in range(self.rank)]
        # run infinite loop for multiple buffers
        while True:
            dump_counter = 0
            # check if dump0 exists, break if false
            cur_file_path = file_frmt.format(buf_counter, 
                                             dump_counter)
            cur_file = Path(cur_file_path)
            if not cur_file.exists():
                break

            # run infinite loop for multiple dumps
            while True:
                # check if file exists, break if false
                cur_file_path = file_frmt.format(buf_counter,
                                                 dump_counter)
                cur_file = Path(cur_file_path)
                if not cur_file.exists():
                    break

                with open(cur_file_path, 'r') as f:
                    l = f.readline()
                    nums = [int(s) for s in l.split()]
                    ranges = []
                    for d in range(0, len(nums), 2):
                        dlows[d//2] = min(nums[d], dlows[d//2])
                        dhighs[d//2] = max(nums[d+1], dhighs[d//2])

                dump_counter += 1
            buf_counter += 1

        return chpl_domain([chpl_range(l,h) for l,h in zip(dlows, dhighs)])

    def compressed_indices(self, file_prefix):

        file_frmt = file_prefix+'_buf{}_dump{}.lz4'
        buf_counter = 0
        # run infinite loop for multiple buffers
        while True:
            dump_counter = 0
            # check if dump0 exists, break if false
            cur_file_path = file_frmt.format(buf_counter, 
                                             dump_counter)
            cur_file = Path(cur_file_path)
            if not cur_file.exists():
                break

            # run infinite loop for multiple dumps
            while True:
                # check if file exists, break if false
                cur_file_path = file_frmt.format(buf_counter,
                                                 dump_counter)
                cur_file = Path(cur_file_path)
                if not cur_file.exists():
                    break

                # decompress and decode into a string
                uncomp = lz4.frame.decompress(cur_file.read_bytes()).decode('utf-8')

                # read string line by line
                for l in uncomp.splitlines():
                    yield self.get_index(l, compressed=True)

                dump_counter += 1
            buf_counter += 1


class MetaLog(object):

    def __init__(self, filename):
        with open(filename) as f:
            # self.rank = get_rank(f.readline())
            self.rank = int(f.readline())
            self.__lh = LogHandler(self.rank)
            self.target_loc_shape = self.__lh.get_index(f.readline())

class LocaleLog(object):

    # TODO rank needs to go
    def __init__(self, filename, rank, no_numpy, debug=False):

        self.__lh = LogHandler(rank)

        self.no_numpy = no_numpy

        with open(filename+'_meta') as f:
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

            offsets = [r.low for r in whole.ranges]
            access_mat_shape = whole.shape()
            # access_mat = np.zeros(access_mat_shape)
            access_mat = AccessMat(access_mat_shape, self.no_numpy)

        # read compressed indices
        if debug:
            print_access_mat(access_mat)
            print()

        max_access = 0
        # import time
        # start_time = time.time()
        self.acc_bbox = self.__lh.access_bbox(filename)
        print('Access bbox ', self.acc_bbox)
        for index in self.__lh.compressed_indices(filename):
            if rank == 1:
                offset_index = index[0] - offsets[0]
            elif rank == 2:
                offset_index = (index[0] - offsets[0],
                                index[1] - offsets[1])
            else:
                offset_index = tuple(i-o for i,o in zip(index, offsets))

            new_val = access_mat[offset_index]+1
            access_mat[offset_index] = new_val
            if new_val > max_access:
                max_access = new_val

        # stop_time = time.time()

        # print('Read time ', stop_time-start_time)
        # import sys
        # sys.exit()

        if debug:
            print_access_mat(access_mat)

        # TODO fix this
        self.rank = rank
        self.whole = whole
        self.subdoms = subdoms
        self.access_mat = access_mat
        self.max_access = max_access

    def gen_total_access(self):
        assert not self.no_numpy
        return int(sum([c for _,c in np.ndenumerate(self.access_mat)]))

    def gen_rar(self):
        assert not self.no_numpy
        num_loc = 0
        num_rem = 0
        for idx,acc_cnt in np.ndenumerate(self.access_mat):
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
        assert not self.no_numpy
        num_rem = 0
        for idx,acc_cnt in np.ndenumerate(self.access_mat):
            if acc_cnt == 0:
                continue

            tmp_loc = False
            for d in self.subdoms:
                if d.member(idx):
                    tmp_loc = True

            if not tmp_loc:
                num_rem += 1

        return float(num_rem)/self.get_num_loc_idxs()

    def gen_access_bbox(self, return_zero_based=True, try_transpose=False):
        if self.acc_bbox is not None:
            return self.acc_bbox

        acc_bbox = chpl_domain([chpl_range(-1,-1)
                                for r in range(self.rank)])

        # for idx,acc_cnt in np.ndenumerate(self.access_mat):
        for _idx,acc_cnt in self.access_mat.enum():
            if return_zero_based:
                idx = _idx
            else:
                idx = to_nonzero_based(_idx, self.whole)

            if acc_cnt > 0:
                acc_bbox = acc_bbox.bbox_expansion(idx)

        self.acc_bbox = acc_bbox

        if try_transpose and acc_bbox.rank==2:
            return acc_bbox.transpose()
        else:
            return acc_bbox

    def gen_access_bbox_efficiency(self):
        assert not self.no_numpy
        bbox = self.acc_bbox

        accessed = 0
        for idx in bbox:
            if self.access_mat[idx] > 0:
                accessed += 1

        return float(accessed)/bbox.size()

    def gen_pairwise_access_bbox(self, llhs, return_zero_based=True,
                                 try_transpose=False):
        assert not self.no_numpy

        self.pwise_bboxes = []
        for ll in llhs:
            acc_bbox = chpl_domain([chpl_range(-1,-1)
                                    for r in range(self.rank)])

            for subdom in ll.subdoms:
                for idx_nz in subdom:
                    idx = to_zero_based(idx_nz, self.whole)
                    if self.access_mat[idx] > 0:
                        # at this point we already checked with the access_mat,
                        # so we need to choose whether we need zero-based
                        # indices or not
                        if return_zero_based:
                            idx_to_add = idx
                        else:
                            idx_to_add = idx_nz

                        if try_transpose and len(idx_to_add) == 2:
                            idx_to_add = (idx_to_add[1],idx_to_add[0])
                        acc_bbox = acc_bbox.bbox_expansion(idx_to_add)

            self.pwise_bboxes.append(acc_bbox)

        return self.pwise_bboxes

    def gen_pwise_access_efficiency(self, llhs):
        assert not self.no_numpy

        pwae = []

        num_contained = 0.
        num_accessed = 0.
        for pwb, llh in zip(self.pwise_bboxes, llhs):
            if pwb.is_empty():
                pwae.append(0.0)
            else:
                for idx in pwb:
                    # check if idx is contained in any of the subdomains
                    contained = False
                    for sd in llh.subdoms:
                        if sd.member(idx):
                            contained = True
                            num_contained += 1
                        break
                    # if the index is contained the data will be
                    # transfered, but the million-dollar question is
                    # whether it will be accessed

                    if contained and self.access_mat[idx] > 0:
                        num_accessed += 1

                # print(pwb, num_accessed, pwb.size(), num_contained)

                pwae.append(num_accessed/num_contained)

        return pwae
                    
    def print_access_mat(self, mat):
        assert not self.no_numpy
        print(self.access_mat)
