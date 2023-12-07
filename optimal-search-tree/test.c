#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for BST
struct Node {
    char key[50];
    char value[50];
    struct Node* left;
    struct Node* right;
};

// Function to create a new Node
struct Node* newNode(char key[], char value[]) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->key, key);
    strcpy(temp->value, value);
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new Node into BST
struct Node* insert(struct Node* root, char key[], char value[]) {
    if (root == NULL) {
        return newNode(key, value);
    }

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->left = insert(root->left, key, value);
    } else if (cmp > 0) {
        root->right = insert(root->right, key, value);
    }

    return root;
}

struct Node* optimizeBST(struct Node* root, int* cost) {
    if (root == NULL) {
        return NULL;
    }

    // Perform DP on left and right subtrees
    root->left = optimizeBST(root->left, cost);
    root->right = optimizeBST(root->right, cost);

    // Initialize cost to the value of the root
    int currentCost = (root->left != NULL ? root->left->value[0] : 0) +
                      (root->right != NULL ? root->right->key[0] : 0);

    // Compare with the minimum cost so far
    if (currentCost < *cost) {
        *cost = currentCost;
        return root;
    }

    // If the root is not the optimal root, try with the left and right children
    struct Node* leftOptimal = (root->left != NULL) ? root->left->right : NULL;
    struct Node* rightOptimal = (root->right != NULL) ? root->right->left : NULL;

    // Check if changing the left child results in a lower cost
    if (leftOptimal != NULL) {
        int leftCost = leftOptimal->value[0] + (root->right != NULL ? root->right->key[0] : 0);
        if (leftCost < *cost) {
            *cost = leftCost;
            return leftOptimal;
        }
    }

    // Check if changing the right child results in a lower cost
    if (rightOptimal != NULL) {
        int rightCost = (root->left != NULL ? root->left->value[0] : 0) + rightOptimal->key[0];
        if (rightCost < *cost) {
            *cost = rightCost;
            return rightOptimal;
        }
    }

    return root;
}


// Function to perform search in optimized BST
char* search(struct Node* root, char key[]) {
    while (root != NULL) {
        int cmp = strcmp(key, root->key);
        if (cmp == 0) {
            return root->value; // Found the key
        } else if (cmp < 0) {
            root = root->left; // Search in the left subtree
        } else {
            root = root->right; // Search in the right subtree
        }
    }

    return "Not Found";
}

// Function to display the optimized BST
void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%s: %s\n", root->key, root->value);
        display(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int n, i;
    char key[50], value[50];

    printf("Enter the number of entries in the dictionary: ");
    scanf("%d", &n);

    printf("Enter the dictionary entries (English word : Indonesian word):\n");
    for (i = 0; i < n; i++) {
        scanf("%s %s", key, value);
        root = insert(root, key, value);
    }

    // Initialize cost to a large value
    int cost = 999999;

    // Optimize the BST using DP
    root = optimizeBST(root, &cost);

    printf("\nOptimized Binary Search Tree:\n");
    display(root);

    // Perform searches in the optimized BST
    printf("\nEnter the English word to search (type 'exit' to stop): ");
    while (1) {
        scanf("%s", key);
        if (strcmp(key, "exit") == 0) {
            break;
        }

        char* result = search(root, key);
        printf("Translation: %s\n", result);
    }

    return 0;
}
