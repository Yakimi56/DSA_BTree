#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10]; // A string representing a name of the vegetable
    int price; // An integer representing the price of the vegetable
} veggie_t; // A struct representing a vegetable

typedef struct node {
    veggie_t data; // The data stored in the node, which is a vegetable
    struct node* pLeft; // A pointer to the left child node
    struct node* pRight; // A pointer to the right child node
} node_t; // A struct representing a node in the binary search tree

veggie_t inputVeggies[] = {
    { "carrot", 0 },
    { "broccoli", 1 },
    { "zucchini", 2 },
    { "tomato", 3 },
    { "eggplant", 4 },
    { "kale", 5 },
    { "pepper", 6 },
    { "potato", 7 },
    { "cabbage", 8 },
    { "spinach", 9 }
}; // An array of vegetables that will be used to build the binary search tree

void binarySearchTree_AddNode(node_t** ppRoot, veggie_t* pVeggie);
// A function to add a new node to the binary search tree
// Takes a pointer to the root node and a pointer to the vegetable to be added

void binarySearchTree_PrintTreeInOrder(node_t* pRoot);
// A function to print the binary search tree in order
// Takes a pointer to the root node

void binarySearchTree_deleteTree(node_t** ppNode);
// A function to delete the binary search tree
// Takes a pointer to the root node

void binarySearchTree_AddNode(node_t** ppRoot, veggie_t* pVeggie) {
    if (*ppRoot == NULL) {
        *ppRoot = malloc(sizeof(node_t));
        (*ppRoot)->data = *pVeggie;
        (*ppRoot)->pLeft = NULL;
        (*ppRoot)->pRight = NULL;
    } else {
        int cmp = strcmp(pVeggie->name, (*ppRoot)->data.name);
        if (cmp < 0) {
            binarySearchTree_AddNode(&(*ppRoot)->pLeft, pVeggie);
        } else if (cmp > 0) {
            binarySearchTree_AddNode(&(*ppRoot)->pRight, pVeggie);
        } else {
            (*ppRoot)->data = *pVeggie;
        }
    }
}
// A recursive function to add a new node to the binary search tree
// If the root node is null, a new node is created with the vegetable data
// If the root node is not null, the function recursively calls itself to find the appropriate location for the new node

void binarySearchTree_PrintTreeInOrder(node_t* pRoot) {
    if (pRoot != NULL) {
        binarySearchTree_PrintTreeInOrder(pRoot->pLeft);
        printf("%s\n", pRoot->data.name);
        binarySearchTree_PrintTreeInOrder(pRoot->pRight);
    }
}
// This function recursively deletes a binary search tree by traversing it in a post-order manner.
// It first deletes the left and right subtrees of the current node, and then deletes the node itself.
// Finally, it sets the node pointer to NULL.
void binarySearchTree_deleteTree(node_t** ppNode) {
    if (*ppNode != NULL) {
        binarySearchTree_deleteTree(&(*ppNode)->pLeft); // Recursively delete the left subtree.
        binarySearchTree_deleteTree(&(*ppNode)->pRight); // Recursively delete the right subtree.
        free(*ppNode); // Free the memory allocated for the current node.
        *ppNode = NULL; // Set the node pointer to NULL.
    }
}

int main() {
    node_t* pRoot = NULL; // Create a pointer to the root node of the binary search tree and initialize it to NULL.

    // Loop through each element in the inputVeggies array and add it to the binary search tree using the binarySearchTree_AddNode function.
    for (int i = 0; i < sizeof(inputVeggies) / sizeof(inputVeggies[0]); i++) {
        binarySearchTree_AddNode(&pRoot, &inputVeggies[i]);
    }

    // Print the keys of the nodes in the binary search tree in ascending order using the binarySearchTree_PrintTreeInOrder function.
    binarySearchTree_PrintTreeInOrder(pRoot);

    // Delete the binary search tree and free its memory using the binarySearchTree_deleteTree function.
    binarySearchTree_deleteTree(&pRoot);

    return 0; // Return 0 to indicate successful program termination.
}

