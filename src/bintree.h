#ifndef __BINTREE__H
#define __BINTREE__H
#include <string.h>

#define datum long long

typedef struct node_ {
  datum value;
  struct node_ * left;
  struct node_ * right;
} node;

typedef struct tree_ {
  node * root;
  size_t size;
} tree;

tree * tree_init();
void tree_destroy(tree * t);
int tree_add(tree * t, datum value);
void tree_walk_preorder(tree * t, void (*walker) (datum value));


#endif
