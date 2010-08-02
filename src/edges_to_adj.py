#!/usr/bin/env python
import sys

def main():
    f = None
    f_new = None
    total_edges = 0

    tos = []
    for line in sys.stdin:
        f_new, to = line[:-1].split("\t", 1)
        f_new = int(f_new)
        to = int(to)
        if to == f_new:
            continue
        if not f_new or not to:
            continue
        if f_new == f:
            tos.append(to)
            continue
        if f is not None:
            tos.sort()
            print " ".join(map(str, tos))
            total_edges += len(tos)
            num_nl = f_new - f - 1
            if num_nl:
                sys.stdout.write("\n" * num_nl)
                sys.stderr.write("Had to skip: %d -- %d\n" % (f, f_new))
        f = f_new
        tos = [to]

    if f:
        tos.sort()
        total_edges += len(tos)
        print " ".join(map(str, tos))
    sys.stderr.write("Total edges: %d\n" % (total_edges / 2))

if __name__ == '__main__':
    main()
