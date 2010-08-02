#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

int node_add(node * n, datum value);
node * node_new(datum value);
void node_walk_preorder(node * n, void (*walker) (datum value));

tree * tree_init()
{
    tree * t = (tree *)malloc(sizeof(tree));
    t->size = 0;
    t->root = NULL;
    return t;
}

void tree_destroy(tree * t)
{
    return;
}

int tree_add(tree * t, datum value)
{
    if (t->root == NULL) {
        t->root = node_new(value);
        ++t->size;
        return 1;
    }

    if (node_add(t->root, value)) {
        ++t->size;
        return 1;
    }
    else {
        return 0;
    }
}

void tree_walk_preorder(tree * t, void (*walker) (datum value))
{
    if (t->root)
        node_walk_preorder(t->root, walker);
}


void node_walk_preorder(node * n, void (*walker) (datum value))
{
    if (n->left)
        node_walk_preorder(n->left, walker);
    (*walker)(n->value);
    if (n->right)
        node_walk_preorder(n->right, walker);
}

int node_add(node * n, datum value)
/* Walker to add a new node. */
{
    if (n->value == value) {
        return 0;
    }
    else if (n->value > value) {
        if (n->left == NULL) {
            n->left = node_new(value);
            return 1;
        }
        else {
            return node_add(n->left, value);
        }
    }
    else {
        if (n->right == NULL) {
            n->right = node_new(value);
            return 1;
        }
        else {
            return node_add(n->right, value);
        }
    }
}

node * node_new(datum value)
{
    node * new = (node *)malloc(sizeof(node));
    new->left = NULL;
    new->right = NULL;
    new->value = value;
    return new;
}
