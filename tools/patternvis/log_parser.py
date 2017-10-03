import re

rank_pattern = r"^([0-9])$"
index_pattern = r"^\(([0-9]+), ([0-9]+)\)$"
domain_pattern_2d = r"^\{([0-9]+)\.\.([0-9]+), ([0-9]+)\.\.([0-9]+)\}$"
domain_pattern = r""

rank = 0

def get_rank(line):
    match = re.match(rank_pattern, line)
    if match:
        return int(match.group(0))
    else:
        print('Invalid rank: ', line)

# returns (xlimits, ylimits)
def generate_limit_tuple(dom_tuple):
    return ((int(dom_tuple[2]), int(dom_tuple[3])), 
            (int(dom_tuple[0]), int(dom_tuple[1])))

def get_dom(line):
    match = re.match(domain_pattern_2d, line)
    if match:
        return generate_limit_tuple(match.groups())
    else:
        # print('Invalid dom: ', line)
        return None

def get_index(line):
    match = re.match(index_pattern, line)
    if match:
        return (int(match.group(1)), int(match.group(2)))
    else:
        print('Invalid index : ', line) 

def print_access_mat(mat):
    for i in range(len(mat)):
        print(mat[i])

def parse_log(filename, debug=False):
    with open(filename) as f:
        rank =  get_rank(f.readline())
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

        #TODO here I assume everything is 0-based
        access_mat_w = whole_lims[0][1]+1
        access_mat_h = whole_lims[1][1]+1
        access_mat = [[0 for x in range(access_mat_w)] for y in
                range(access_mat_h)]

        if debug:
            print_access_mat(access_mat)
            print()

        max_access = 0
        for line in f:
            index = get_index(line)
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
