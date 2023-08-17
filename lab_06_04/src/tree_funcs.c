#include "../inc/tree_funcs.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tree_node *find_minimum(tree_node *current_node)
{
    if (current_node->left == NULL)
        return current_node;

    return find_minimum(current_node->left);
}

int tree_search(tree_node *root, void *value, int cmpfunc(void *, void *))
{
    if (root == NULL)
        return 0;
    tree_node *current_node = root;
    int flag = 0;

    while (1)
    {
        if (cmpfunc(value, current_node->val) == 0)
        {
            flag = 1;
            break;
        }
        else if (cmpfunc(value, current_node->val) <= 0)
            current_node = current_node->left;
        else
            current_node = current_node->right;

        if (current_node == NULL)
            break;
    }
    return flag;
}

int cmp_int(void *ptr1, void *ptr2)
{
    return *((int *)ptr1) - *((int *)ptr2);
}

void print_int(tree_node *ptr, void *param)
{
    const char *fmt = param;

    printf(fmt, *(int *)(ptr->val));
}

void insert(tree_node **root, void *value, int cmpfunc(void *, void *))
{
    tree_node *temp_node;
    tree_node *current_node;
    tree_node *parent_node;

    temp_node = malloc(sizeof(tree_node));
    // int *val_ptr = malloc(sizeof(int));
    //*val_ptr = value;
    temp_node->val = value;
    temp_node->left = NULL;
    temp_node->right = NULL;

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
            if (cmpfunc(value, parent_node->val) <= 0)
            {
                current_node = current_node->left;

                if (current_node == NULL)
                {
                    parent_node->left = temp_node;
                    return;
                }
            }
            else
            {
                current_node = current_node->right;

                if (current_node == NULL)
                {
                    parent_node->right = temp_node;
                    return;
                }
            }
        }
    }
}

void node_to_dot_int(struct tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", *(int *)tree->val, *(int *)tree->left->val);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", *(int *)tree->val, *(int *)tree->right->val);
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

    apply_pre(root, node_to_dot_int, f);

    fprintf(f, "}\n");
}

void free_node(tree_node *ptr, void *param)
{
    (void)param;
    // free(ptr->val);
    free(ptr);
}

void free_tree(tree_node *root)
{
    apply_post(root, free_node, NULL);
}

tree_node *delete_node(tree_node *root, void *value, int cmpfunc(void *, void *))
{
    if (root == NULL)
    {
        return root;
    }

    // if (key < root.key)
    if (cmpfunc(value, root->val) < 0)
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
}

tree_node *delete_node_less_than_tmp(tree_node *root, void *value, int cmpfunc(void *, void *), int *rc)
{

    if (root == NULL)
    {
        return root;
    }

    if (cmpfunc(value, root->val) < 0)
    {
        root->left = delete_node_less_than_tmp(root->left, value, cmpfunc, rc);
    }
    else
    {
        if (root->left == NULL)
        {
            *rc = 1;
            tree_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            *rc = 1;
            tree_node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            *rc = 1;
            tree_node *temp = find_minimum(root->right);
            // free(root->val);
            root->val = temp->val;
            root->right = delete_node_less_than_tmp(root->right, temp->val, cmpfunc, rc);
        }
    }
    return root;
}

void delete_node_less_than(tree_node **root, void *value, int cmpfunc(void *, void *))
{
    int rc = 1;
    while (rc == 1)
    {
        rc = 0;
        *root = delete_node_less_than_tmp(*root, value, cmpfunc, &rc);
    }
}

void node_to_dot_file(tree_node *tree, void *param)
{
    FILE *f = param;
    char str1[50];
    char str2[50];
    if (tree->left)
    {
        file_info *tree1 = tree->val;
        file_info *tree2 = tree->left->val;
        snprintf(str1, 50, "%d.%d.%d", tree1->day, tree1->month, tree1->year);
        snprintf(str2, 50, "%d.%d.%d", tree2->day, tree2->month, tree2->year);

        fprintf(f, "\"%s\\n%s\" -> \"%s\\n%s\";\n", tree1->filename, str1, tree2->filename, str2);
    }

    if (tree->right)
    {
        file_info *tree1 = tree->val;
        file_info *tree2 = tree->right->val;
        snprintf(str1, 50, "%d.%d.%d", tree1->day, tree1->month, tree1->year);
        snprintf(str2, 50, "%d.%d.%d", tree2->day, tree2->month, tree2->year);

        fprintf(f, "\"%s\\n%s\" -> \"%s\\n%s\";\n", tree1->filename, str1, tree2->filename, str2);
    }
}

void tree_export_f(FILE *f, const char *tree_name, tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_in(tree, node_to_dot_file, f);

    fprintf(f, "}\n");
}

int find_non_sorted(tree_node *root, int val)
{
    if (root == NULL)
        return -1;
    if (*(int *)(root->val) == val)
        return 0;
    int rc = find_non_sorted(root->left, val);
    if (rc != 0)
        rc = find_non_sorted(root->right, val);
    return rc;
}

tree_node *gen_tree(double branching, int node_num)
{
    int index = 1;
    int *val = my_malloc(sizeof(int));
    *val = index;
    tree_node *root = NULL;
    insert(&root, val, cmp_int);

    int childs = (double)(node_num / 2) * branching;

    int left_branch = (node_num - childs) / 2;
    int right_branch = node_num - childs - left_branch;

    int left_childs = childs / 2;
    int right_childs = childs - left_childs;

    /*printf("INFO:\n");
    printf("left branch: %d\n", left_branch);
    printf("right branch: %d\n", right_branch);
    printf("left child: %d\n", left_childs);
    printf("right child: %d\n", right_childs);*/

    tree_node *cur_node = root;

    for (int i = 0; i < left_branch; i++)
    {
        tree_node *temp_node = malloc(sizeof(tree_node));
        val = my_malloc(sizeof(int));
        index++;
        *val = index;
        temp_node->val = val;
        temp_node->left = NULL;
        temp_node->right = NULL;

        cur_node->left = temp_node;
        cur_node = temp_node;
    }

    cur_node = root;

    for (int i = 0; i < right_branch; i++)
    {
        tree_node *temp_node = malloc(sizeof(tree_node));
        val = my_malloc(sizeof(int));
        index++;
        *val = index;
        temp_node->val = val;
        temp_node->left = NULL;
        temp_node->right = NULL;

        cur_node->right = temp_node;
        cur_node = temp_node;
    }

    cur_node = root->left;

    for (int i = 0; i < left_childs; i++)
    {
        tree_node *temp_node = malloc(sizeof(tree_node));
        val = my_malloc(sizeof(int));
        index++;
        *val = index;
        temp_node->val = val;
        temp_node->left = NULL;
        temp_node->right = NULL;

        cur_node->right = temp_node;
        cur_node = cur_node->left;
    }
    cur_node = root->right;
    for (int i = 0; i < right_childs; i++)
    {
        tree_node *temp_node = malloc(sizeof(tree_node));
        val = my_malloc(sizeof(int));
        index++;
        *val = index;
        temp_node->val = val;
        temp_node->left = NULL;
        temp_node->right = NULL;

        cur_node->left = temp_node;
        cur_node = cur_node->right;
    }
    return root;
}