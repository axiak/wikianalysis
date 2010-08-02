#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bintree.h"

#define CREATE_PAIR(a, b) (a > b) ? \
  ((((long long)a) << 32) + ((long long)b)) :	\
  ((((long long)b) << 32) + ((long long)a))

#define SPLIT_PAIR(pair, a, b) do { \
    a = (pair) & 0xFFFFFFFF; b = (pair) >> 32;	\
  } while (0)

#define BUFSIZE 262144

void walker(datum value);

int main(int argc, char ** argv)
{
    char * linebuf = (char *)malloc(BUFSIZE);
    char * pch;
    tree * t = tree_init();
    int i, lines=0;
    long from, to;

    if (!linebuf) {
        fprintf(stderr, "Memory error\n");
        return 1;
    }

    while (fgets(linebuf, BUFSIZE, stdin)) {
        for (i = 0, pch = strtok(linebuf, "\t"); pch != NULL; ++i, pch = strtok(NULL, "\t")) {
            if (!i) {
                from = atol(pch);
            }
            else {
                to = atol(pch);
            }
            tree_add(t, CREATE_PAIR(from, to));
        }
        if ((++lines) % 10000 == 0) {
            fprintf(stderr, "Finished with %d lines.\n", lines);
        }
    }
    tree_walk_preorder(t, &walker);

    return 0;
}

void walker(datum value) {
    long from, to;

    SPLIT_PAIR(value, from, to);
    printf("%lu\t%lu\n", from, to);
    printf("%lu\t%lu\n", to, from);
}
