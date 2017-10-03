import re

rank_pattern = r"^([0-9])$"
index_pattern_2d = r"^\(([0-9]+), ([0-9]+)\)$"
index_pattern_1d = r"^\(([0-9]+)\)$"
domain_pattern_2d = r"^\{([0-9]+)\.\.([0-9]+), ([0-9]+)\.\.([0-9]+)\}$"
domain_pattern_1d = r"^\{([0-9]+)\.\.([0-9]+)\}$"
domain_pattern = r""
index_pattern = r""

rank = 0

def get_rank(line):
    match = re.match(rank_pattern, line)
    if match:
        return int(match.group(0))
    else:
        print('Invalid rank: ', line)

# returns (xlimits, ylimits)
def generate_limit_tuple(dom_tuple):
    global rank
    if rank == 1 :
        return ( (int(dom_tuple[0]), int(dom_tuple[1])), )
    elif rank == 2:
        return ((int(dom_tuple[2]), int(dom_tuple[3])), 
                (int(dom_tuple[0]), int(dom_tuple[1])))

def get_dom(line):
    print(domain_pattern)
    match = re.match(domain_pattern, line)
    if match:
        return generate_limit_tuple(match.groups())
    else:
        # print('Invalid dom: ', line)
        return None

# TODO maybe change to get_tuple ?
def get_index(line):
    print(index_pattern)
    match = re.match(index_pattern, line)
    if match:
        if rank == 1:
            return (int(match.group(1)), )
        elif rank == 2:
            return (int(match.group(1)), int(match.group(2)))
    else:
        print('Invalid index : ', line) 

def print_access_mat(mat):
    for i in range(len(mat)):
        print(mat[i])

rank = 0
def parse_meta_log(filename):
    global rank
    global index_pattern
    global index_pattern_2d
    global domain_pattern
    global domain_pattern_2d

    with open(filename) as f:
        rank = get_rank(f.readline())
        if rank == 1:
            domain_pattern = domain_pattern_1d
            index_pattern = index_pattern_1d
        if rank == 2:
            domain_pattern = domain_pattern_2d
            index_pattern = index_pattern_2d
        target_loc_shape = get_index(f.readline())
    # print(index_pattern)
    return target_loc_shape

def parse_log(filename, debug=False):

    with open(filename) as f:
        # rank =  get_rank(f.readline())
        global rank
        whole_lims= get_dom(f.readline())

        # now start reading subdomain(s). At this point we do not know
        # how many there are, so we do some regexp checking for each
        # line we read to determine whether it is a domain or an index
        subdom_lims = []
        tmp_line = f.readline()
        dom = get_dom(tmp_line)

        while dom != None:
            subdom_lims.append(dom)
            last_pos = f.tell()
            tmp_line = f.readline()
            dom = get_dom(tmp_line)

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
            real_index = get_index(line)
            if rank == 1:
                index = (real_index[0]-d1_offset, 0)
            elif rank == 2:
                index = (real_index[0]-d1_offset, real_index[1]-d2_offset)
            access_mat[index[0]][index[1]] += 1
            if access_mat[index[0]][index[1]] > max_access:
                max_access = access_mat[index[0]][index[1]] 

        if debug:
            print_access_mat(access_mat)

    return (rank, whole_lims, subdom_lims, access_mat, max_access)

if __name__ == "__main__":
    print('LOCALE0')
    parse_log('arrlocale_0', debug = True)
    print('LOCALE1')
    parse_log('arrlocale_1', debug = True)
