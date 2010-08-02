#!/usr/bin/env python
" Fix redirects "

def main():
    d = create_map()
    remap_file(d)

def remap_file(d):
    f = open('/mnt/data/wp_adjlist.dat')
    output = open('/mnt/data/wp_adjlistr.dat', 'w+')

    for line in f:
        if '\tR:' in line:
            continue
        line = line[:-1]
        cols = line.split("\t")
        for i in range(1, len(cols)):
            t = cols[i]
            loc = t.find('#')
            if loc > -1:
                t = t[:loc]
            cols[i] = d.get(t, t)
        output.write("\t".join(cols) + "\n")


def create_map():    
    f = open('/mnt/data/redirects.dat')
    map = {}
    for line in f:
        line = line[:-1]
        if '\tR:' not in line:
            continue
        key, value = line.split('\tR:', 1)
        map[key] = value
    return map
        

if __name__ == '__main__':
    main()
