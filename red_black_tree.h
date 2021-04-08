#include "variables.h"
///source: https://www.geeksforgeeks.org/left-leaning-red-black-tree-insertion/


typedef struct datarb {
    char name[VELA];
    int birthday;
} DATARB;

typedef struct noderb {
    struct noderb *left, *right;
    DATARB *data;
    int color; //red=1 black=0
} NODERB;


// utility function to create a node.
NODERB *createNode(DATARB *data, int color) {
    NODERB *myNode = (NODERB *) malloc(sizeof(NODERB));
    myNode->left = myNode->right = NULL;
    myNode->data = data;

    // New Node which is created is
    // always red in color.
    myNode->color = 1;
    return myNode;
}

// utility function to rotate node anticlockwise.
NODERB *rotateLeft(NODERB *myNode) {
    //printf("left rotation!!\n");
    NODERB *child = myNode->right;
    NODERB *childLeft = child->left;

    child->left = myNode;
    myNode->right = childLeft;

    return child;
}

// utility function to rotate node clockwise.
NODERB *rotateRight(NODERB *myNode) {
    //printf("right rotation\n");
    NODERB *child = myNode->left;
    NODERB *childRight = child->right;

    child->right = myNode;
    myNode->left = childRight;

    return child;
}

// utility function to check whether
// node is red in color or not.
int isRed(NODERB *myNode) {
    if (myNode == NULL)
        return 0;
    return (myNode->color == 1);
}

// utility function to swap color of two
// nodes.
void swapColors(NODERB *node1, NODERB *node2) {
    int temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
}

// insertion into Left Leaning Red Black Tree.
NODERB *insert(NODERB *myNode, DATARB *datarb) {
    // Normal insertion code for any Binary
    // Search tree.
    if (myNode == NULL)
        return createNode(datarb, 0);

    if (0 < strcmp(datarb->name, myNode->data->name))
        myNode->left = insert(myNode->left, datarb);

    else if (0 > strcmp(datarb->name, myNode->data->name))
        myNode->right = insert(myNode->right, datarb);

    else
        return myNode;


    // case 1.
    // when right child is Red but left child is
    // Black or doesn't exist.
    if (isRed(myNode->right) && !isRed(myNode->left)) {
        // left rotate the node to make it into
        // valid structure.
        myNode = rotateLeft(myNode);

        // swap the colors as the child node
        // should always be red
        swapColors(myNode, myNode->left);

    }

    // case 2
    // when left child as well as left grand child in Red
    if (isRed(myNode->left) && isRed(myNode->left->left)) {
        // right rotate the current node to make
        // it into a valid structure.
        myNode = rotateRight(myNode);
        swapColors(myNode, myNode->right);
    }


    // case 3
    // when both left and right child are Red in color.
    if (isRed(myNode->left) && isRed(myNode->right)) {
        // invert the color of node as well
        // it's left and right child.
        myNode->color = !myNode->color;

        // change the color to black.
        myNode->left->color = 0;
        myNode->right->color = 0;
    }

    return myNode;
}
NODERB *searchRB(NODERB *root, DATARB *key)
{
    if (!root||!strcmp(key->name, root->data->name))
        return root;
    if (0 > strcmp(key->name, root->data->name))
        searchRB(root->left,key);
    if (0 < strcmp(key->name, root->data->name))
        searchRB(root->right,key);
}
