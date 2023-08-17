#include <stdio.h>

#ifndef __SEARCH_TREE__

#define __SEARCH_TREE__

/*
Узел дерева
*/
typedef struct tree_node
{
    char *name; //Ключевое слово
    char *desc; //Описание

    struct tree_node *left;  //Левое поддерево
    struct tree_node *right; //Правое поддерево

    unsigned char height; //Высота ветки

    // tree_node(int k) { key = k; left = right = 0; height = 1; }
} tree_node;

// trc-ignore
typedef void (*ptr_action_t)(struct tree_node *, void *);

// trc-ignore
tree_node *find_minimum(tree_node *current_node);
// trc-ignore
tree_node *tree_search(tree_node *root, char *value, int *cmpnum);
// trc-ignore
void insert(tree_node **root, char *name, char *desc);
// trc-ignore
void node_to_dot(struct tree_node *tree, void *param);
// trc-ignore
void apply_pre(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void apply_in(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void apply_post(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void tree_export(FILE *f, const char *tree_name, tree_node *root);
// trc-ignore
void free_node(tree_node *ptr, void *param);
// trc-ignore
void free_tree(tree_node *root);
// trc-ignore
unsigned char tree_height(tree_node *p);
// trc-ignore
int tree_bfactor(tree_node *p);
// trc-ignore
void tree_fixheight(tree_node *p);
// trc-ignore
tree_node *tree_rotateright(tree_node *p);
// trc-ignore
tree_node *tree_rotateleft(tree_node *q);
// trc-ignore
tree_node *tree_balance(tree_node *p);
// trc-ignore
tree_node *insert_balanced(tree_node *root, char *name, char *desc);

#endif