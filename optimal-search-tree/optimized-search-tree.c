#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char key[50];
    char value[50];
    int height;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(char key[], char value[]) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->key, key);
    strcpy(temp->value, value);
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int getBalance(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node* insertAVL(struct Node* root, char key[], char value[]) {
    if (root == NULL) {
        return newNode(key, value);
    }

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->left = insertAVL(root->left, key, value);
    } else if (cmp > 0) {
        root->right = insertAVL(root->right, key, value);
    } else {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && strcmp(key, root->left->key) < 0) {
        return rightRotate(root);
    }
    if (balance < -1 && strcmp(key, root->right->key) > 0) {
        return leftRotate(root);
    }
    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* optimizeBST(struct Node* root, int* cost) {
    if (root == NULL) {
        return NULL;
    }

    root->left = optimizeBST(root->left, cost);
    root->right = optimizeBST(root->right, cost);

    int currentCost = (root->left != NULL ? root->left->height : 0) +
                      (root->right != NULL ? root->right->height : 0);

    if (currentCost < *cost) {
        *cost = currentCost;
        return root;
    }

    struct Node* leftOptimal = (root->left != NULL) ? root->left->right : NULL;
    struct Node* rightOptimal = (root->right != NULL) ? root->right->left : NULL;

    if (leftOptimal != NULL) {
        int leftCost = leftOptimal->height + (root->right != NULL ? root->right->height : 0);
        if (leftCost < *cost) {
            *cost = leftCost;
            return leftOptimal;
        }
    }

    if (rightOptimal != NULL) {
        int rightCost = (root->left != NULL ? root->left->height : 0) + rightOptimal->height;
        if (rightCost < *cost) {
            *cost = rightCost;
            return rightOptimal;
        }
    }

    return root;
}

char* search(struct Node* root, char key[]) {
    while (root != NULL) {
        int cmp = strcmp(key, root->key);
        if (cmp == 0) {
            return root->value;
        } else if (cmp < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return "Not Found";
}

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
        root = insertAVL(root, key, value);
    }

    int cost = 999999;
    root = optimizeBST(root, &cost);

    printf("\nOptimized AVL Tree:\n");
    display(root);

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
