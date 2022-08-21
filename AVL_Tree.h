#include<stdio.h>
#include<stdlib.h>

typedef int element_type;

struct avl_node;
typedef struct avl_node* position;
typedef struct avl_node* avl_tree;

avl_tree make_empty(avl_tree t);
position find(element_type x, avl_tree t);
position find_min(avl_tree t);
position find_max(avl_tree t);
avl_tree insert(element_type x, avl_tree t);
avl_tree deletenote(element_type x, avl_tree t);

position single_rotate_with_left_left(position k2);// ×ó×óµ¥Ðý×ª
position single_rotate_with_right_right(position k2);// ÓÒÓÒµ¥Ðý×ª
position double_rotate_with_left_right(position k3);// ×óÓÒË«Ðý×ª
position double_rotate_with_right_left(position k3);// ÓÒ×óË«Ðý×ª

int height(position p);
int max(int a, int b);
void print_tree(int depth, int left, avl_tree t);
#define error(str) fatal_error(str)
#define fatal_error(str) fprintf(stderr, "%s\n", str),exit(1)

struct avl_node
{
    element_type element;
    avl_tree left;
    avl_tree right;
    int height;
};

int height(position p)
{
    if (NULL == p)
        return -1;
    else
        return p->height;
}

position find(element_type x, avl_tree t)
{
    if (NULL == t)
        return NULL;
    if (x > t->element)
        return find(x, t->right);
    else if (x < t->element)
        return find(x, t->left);
    else
        return t;
}

position find_min(avl_tree t)
{
    if (NULL != t)
        while (NULL != t->left)
            t = t->left;
    return t;
}

position find_max(avl_tree t)
{
    if (NULL == t)
        return NULL;

    if (NULL == t->right)
        return t;
    else
        return find_max(t->right);
}

avl_tree deletenote(element_type x, avl_tree t)
{
    position temp;
    if (NULL == t)
        error("empty tree");

    if (x > t->element)
        t->right = deletenote(x, t->right);
    else if (x < t->element)
        t->left = deletenote(x, t->left);
    else if (t->left && t->right) {
        temp = find_min(t->right);
        t->element = temp->element;
        t->right = deletenote(t->element, t->right);
    }
    else {
        temp = t;
        if (NULL == t->left)
            t = t->right;
        else if (NULL == t->right)
            t = t->left;
        free(temp);
        temp = NULL;
    }
    return t;
}

avl_tree make_empty(avl_tree t)
{
    if (NULL != t) {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }

    return NULL;
}

avl_tree insert(element_type x, avl_tree t)
{
    if (NULL == t) {
        t = (avl_tree)malloc(sizeof(struct avl_node));
        if (NULL == t)
            fatal_error("out of space");
        t->element = x;
        t->left = t->right = NULL;
        t->height = 0;
    }
    else if (x < t->element) {
        t->left = insert(x, t->left);
        if ((height(t->left) - height(t->right)) == 2) {
            if (x < t->left->element)
                t = single_rotate_with_left_left(t);
            else
                t = double_rotate_with_left_right(t);
        }
    }
    else if (x > t->element) {
        t->right = insert(x, t->right);
        if ((height(t->right) - height(t->right)) == 2) {
            if (x > t->right->element)
                t = single_rotate_with_right_right(t);
            else
                t = double_rotate_with_right_left(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}


position single_rotate_with_left_left(position k2)
{
    position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    return k1;
}

position single_rotate_with_right_right(position k2)
{
    position k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    return k1;
}

position double_rotate_with_left_right(position k3)
{
    k3->left = single_rotate_with_right_right(k3->left);
    return single_rotate_with_left_left(k3);
}

position double_rotate_with_right_left(position k3)
{
    k3->right = single_rotate_with_left_left(k3->right);
    return single_rotate_with_right_right(k3);
}
int max(int a, int b)
{
    return a > b ? a : b;
}

void print_tree(int depth, int left, avl_tree t)
{
    int i;
    if (t) {
        for (i = 0; i < left; i++)
            printf("    ");
        printf("%d\n", t->element);
        print_tree(depth + 1, left - 1, t->left);
        print_tree(depth + 1, left + 1, t->right);
    }
}

