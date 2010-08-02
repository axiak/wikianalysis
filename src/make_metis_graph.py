#!/usr/bin/env python



def main():
    adj = open("/mnt/data/wp_adjlistr.dat")
    new_idmap = open("/mnt/data/newidmap.dat", "w+")
    new_adjlist = open("/mnt/data/wp_adjlistg.dat", "w+")
    mapper = DictInt(new_idmap)

    num_edges = 0
    num_vertices = 0

    for line in adj:
        line = line[:-1]
        if not line:
            continue
        cols = map(mapper.get_id, line.split('\t'))
        num_edges += len(cols) - 1
        new_adjlist.write("\t".join(cols) + "\n")
        num_vertices += 1

    print "Num vertices: %d, num edges: %d\n" % (num_vertices, num_edges)


class DictInt(object):
    def __init__(self, file):
        self.file = file
        self.d = {}

    def get_id(self, s):
        if s in self.d:
            return str(self.d[s])
        id = len(self.d) + 1
        self.d[s] = id
        self.file.write("%s\t%d\n" % (s, id))
        return str(id)


if __name__ == '__main__':
    main()
