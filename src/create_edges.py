#!/usr/bin/env python
import sys

def main():
    edges = set()
    for line in sys.stdin:
        line = line[:-1]
        if not line:
            continue
        cols = map(int, line.split('\t'))
        from_ = cols[0]
        for to in cols[1:]:
            if from_ < to:
                edge = (from_, to)
            else:
                edge = (to, from_)
            edges.add(edge)
    for edge in edges:
        print edge[0] + "\t" + edge[1]
        print edge[1] + "\t" + edge[0]


if __name__ == '__main__':
    main()
