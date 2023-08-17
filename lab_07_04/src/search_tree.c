#include "../inc/search_tree.h"

#include "../inc/dynamic_data.h"
#include "../inc/menu_funcs.h"
#include "../inc/my_defines.h"
#include "../inc/search_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tree_node *find_minimum(tree_node *current_node)
{
    if (current_node->left == NULL)
        return current_node;

    return find_minimum(current_node->left);
}

tree_node *tree_search(tree_node *root, char *value, int *cmpnum)
{
    (*cmpnum) = 0;
    if (root == NULL)
        return NULL;
    tree_node *current_node = root;
    tree_node *flag = NULL;

    while (1)
    {
        // if (cmpfunc(value, current_node->name) == 0)
        (*cmpnum)++;
        if (strcmp(value, current_node->name) == 0)
        {
            flag = current_node;
            break;
            (*cmpnum)++;
        }
        else if (strcmp(value, current_node->name) <= 0)
            current_node = current_node->left;
        else
            current_node = current_node->right;

        if (current_node == NULL)
            break;
    }
    return flag;
}

void insert(tree_node **root, char *name, char *desc)
{
    tree_node *temp_node;
    tree_node *current_node;
    tree_node *parent_node;

    temp_node = malloc(sizeof(tree_node));
    // int *val_ptr = malloc(sizeof(int));
    //*val_ptr = value;
    temp_node->name = name;
    temp_node->desc = desc;

    temp_node->left = NULL;
    temp_node->right = NULL;

    temp_node->height = 1;

    // node(int k) { key = k; left = right = 0; height = 1; }

    // For the very first call
    if (*root == NULL)
    {
        *root = temp_node;
    }
    else
    {
        current_node = *root;
        parent_node = NULL;

        while (1)
        {
            parent_node = current_node;

            // if (value <= *((int *)parent_node->val))
            // if (cmpfunc(value, parent_node->val) <= 0)
            if (strcmp(name, parent_node->name) <= 0)
            {
                current_node = current_node->left;

                if (current_node == NULL)
                {
                    parent_node->left = temp_node;
                    //*root = tree_balance(parent_node);
                    return;
                }
            }
            else
            {
                current_node = current_node->right;

                if (current_node == NULL)
                {
                    parent_node->right = temp_node;
                    //*root = tree_balance(parent_node);
                    return;
                }
            }
        }
    }
}

tree_node *insert_balanced(tree_node *root, char *name, char *desc)
{
    if (root == NULL)
    {
        tree_node *temp_node;

        temp_node = malloc(sizeof(tree_node));

        temp_node->name = name;
        temp_node->desc = desc;

        temp_node->left = NULL;
        temp_node->right = NULL;

        temp_node->height = 1;

        return temp_node;
    }

    if (strcmp(name, root->name) < 0)
    {
        root->left = insert_balanced(root->left, name, desc);
    }
    else
    {
        root->right = insert_balanced(root->right, name, desc);
    }
    return tree_balance(root);

    // if (!p)
    // return new node(k);
    /*if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);*/
}

void node_to_dot(struct tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
    {
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);
    }

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);
}

void apply_pre(struct tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void apply_in(struct tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    apply_in(tree->left, f, arg);
    f(tree, arg);
    apply_in(tree->right, f, arg);
}

void apply_post(struct tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    apply_post(tree->left, f, arg);
    apply_post(tree->right, f, arg);
    f(tree, arg);
}

void tree_export(FILE *f, const char *tree_name, tree_node *root)
{
    fprintf(f, "digraph \"%s\" {\n", tree_name);

    apply_pre(root, node_to_dot, f);

    fprintf(f, "}\n");
}

void free_node(tree_node *ptr, void *param)
{
    (void)param;
    free(ptr->desc);
    free(ptr->name);
    free(ptr);
}

void free_tree(tree_node *root)
{
    apply_post(root, free_node, NULL);
}

unsigned char tree_height(tree_node *p)
{
    return p ? p->height : 0;
}

int tree_bfactor(tree_node *p)
{
    return tree_height(p->right) - tree_height(p->left);
}

void tree_fixheight(tree_node *p)
{
    unsigned char hl = tree_height(p->left);
    unsigned char hr = tree_height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

tree_node *tree_rotateright(tree_node *p)
{
    tree_node *q = p->left;
    p->left = q->right;
    q->right = p;
    tree_fixheight(p);
    tree_fixheight(q);
    return q;
}

tree_node *tree_rotateleft(tree_node *q)
{
    tree_node *p = q->right;
    q->right = p->left;
    p->left = q;
    tree_fixheight(q);
    tree_fixheight(p);
    return p;
}

tree_node *tree_balance(tree_node *p)
{
    tree_fixheight(p);
    if (tree_bfactor(p) == 2)
    {
        if (tree_bfactor(p->right) < 0)
            p->right = tree_rotateright(p->right);
        return tree_rotateleft(p);
    }
    if (tree_bfactor(p) == -2)
    {
        if (tree_bfactor(p->left) > 0)
            p->left = tree_rotateleft(p->left);
        return tree_rotateright(p);
    }
    return p; // балансировка не нужна
}

/*
tree_node *delete_node(tree_node *root, void *value, int cmpfunc(void *, void *))
{
    if (root == NULL)
    {
        return root;
    }

    // if (key < root.key)
    //if (cmpfunc(value, root->val) < 0)
    if(strcmp)
    {
        root->left = delete_node(root->left, value, cmpfunc);
    }
    else if (cmpfunc(value, root->val) > 0)
    {
        root->right = delete_node(root->right, value, cmpfunc);
    }
    else
    {
        if (root->left == NULL)
        {
            tree_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            tree_node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            tree_node *temp = find_minimum(root->right);
            // free(root->val);
            root->val = temp->val;
            root->right = delete_node(root->right, temp->val, cmpfunc);
        }
    }
    return root;
}*/