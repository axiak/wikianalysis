edges: create_edges.c
	gcc -Wall -O3 create_edges.c bintree.c -o create_edges

edgescpp: create_edges.cpp
	g++ -Wall -O3 create_edges.cpp -o create_edges

parser: parse_bzip2.cpp
	g++ -Wall -O3 -lre2 -I/usr/include/re2 parse_bzip2.cpp -o parse_bzip2
