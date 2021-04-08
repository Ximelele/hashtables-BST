#include "variables.h"
#define VELA 100

typedef struct data {
    char name[VELA];
    int birthday;
} DATA;

typedef struct node {
    DATA *data;
    int height;
    struct node *left;
    struct node *right;
} NODE;


int max(int a, int b) {
    return (a > b) ? a : b;
}

NODE *create_node(DATA *data) {
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(NODE *rootAVL) {
    if (rootAVL == NULL)
        return 0;
    return rootAVL->height;
}


NODE *rotate_right(NODE *rootAvl) {
    //root of subtree
    NODE *x = rootAvl->left;
    //child of x
    NODE *z = x->right;

    x->right = rootAvl;
    rootAvl->left = z;

    rootAvl->height = max(height(rootAvl->left), height(rootAvl->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;

}

//wikipedia magic
NODE *rotate_left(NODE *rootAvl) {
    //root of subtree
    NODE *x = rootAvl->right;
    //child of x
    NODE *z = x->left;

    x->left = rootAvl;
    rootAvl->right = z;

    rootAvl->height = max(height(rootAvl->left), height(rootAvl->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;


    return x;
}
int Balance(NODE *rooAVL)
{
    if (rooAVL == NULL)
        return 0;
    return height(rooAVL->left) - height(rooAVL->right);
}
NODE *insert_avl(NODE *rootAVL, DATA *data) {

    if (rootAVL == NULL)
        return create_node(data);

    if (0<strcmp(data->name,rootAVL->data->name))
        rootAVL->left = insert_avl(rootAVL->left, data);

    else if (0>strcmp(data->name,rootAVL->data->name))
        rootAVL->right = insert_avl(rootAVL->right, data);
    else
        return rootAVL;

    rootAVL->height = max(height(rootAVL->left), height(rootAVL->right)) +1;

    int to_balance=Balance(rootAVL);

    //left left
    if (to_balance > 1 && 0<strcmp(data->name,rootAVL->left->data->name))
        return rotate_right(rootAVL);
    //right right
    if (to_balance < -1 && 0>strcmp(data->name,rootAVL->right->data->name))
        return rotate_left(rootAVL);
    //left right
    if (to_balance > 1 && 0>strcmp(data->name,rootAVL->left->data->name)) {
        rootAVL->left = rotate_left(rootAVL->left);
        return rotate_right(rootAVL);
    }
    if (to_balance < -1 && 0<strcmp(data->name,rootAVL->right->data->name)) {
        rootAVL->right = rotate_right(rootAVL->right);
        return rotate_left(rootAVL);
    }


    return rootAVL;

}

NODE *search_avl(NODE *rootAvl, DATA *data) {

        if (!rootAvl||!strcmp(data->name, rootAvl->data->name))
            return rootAvl;
        if (0 > strcmp(data->name, rootAvl->data->name))
            search_avl(rootAvl->left,data);
        if (0 < strcmp(data->name, rootAvl->data->name))
            search_avl(rootAvl->right,data);
}


