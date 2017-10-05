import re

class LogHandler(object):

    # TODO do these programmatically
    def __init__(self, rank):
        rank_pattern = r"^([0-9])$"
        index_pattern_2d = r"^\(([0-9]+), ([0-9]+)\)$"
        index_pattern_1d = r"^\(([0-9]+)\)$"
        domain_pattern_2d = r"^\{([0-9]+)\.\.([0-9]+), ([0-9]+)\.\.([0-9]+)\}$"
        domain_pattern_1d = r"^\{([0-9]+)\.\.([0-9]+)\}$"
        domain_pattern = r""
        index_pattern = r""
        self.rank = rank
        if rank == 1:
            self.domain_pattern = domain_pattern_1d
            self.index_pattern = index_pattern_1d
        if rank == 2:
            self.domain_pattern = domain_pattern_2d
            self.index_pattern = index_pattern_2d

    # returns (xlimits, ylimits)
    def generate_limit_tuple(self, dom_tuple):
        if self.rank == 1 :
            return ( (int(dom_tuple[0]), int(dom_tuple[1])), )
        elif self.rank == 2:
            return ((int(dom_tuple[2]), int(dom_tuple[3])), 
                    (int(dom_tuple[0]), int(dom_tuple[1])))

    def get_dom(self, line):
        match = re.match(self.domain_pattern, line)
        if match:
            return self.generate_limit_tuple(match.groups())
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

        self.rank = rank
        self.whole_lims = whole_lims
        self.subdom_lims = subdom_lims
        self.access_mat = access_mat
        self.max_access = max_access

    def print_access_mat(self, mat):
        for i in range(len(mat)):
            print(mat[i])
