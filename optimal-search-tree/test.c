#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node {
    char key[100];
    char value[100];
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(char key[], char value[]) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (temp != NULL) {
        strcpy(temp->key, key);
        strcpy(temp->value, value);
        temp->left = temp->right = NULL;
    }
    return temp;
}

// Updated insert function
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

char* search(struct Node* root, char key[]) {
    while (root != NULL) {
        // Jika kata kunci cocok dengan awalan pada node
        if (strstr(root->key, key) == root->key) {
            return root->value; // Found the key
        } else if (strcmp(key, root->key) < 0) {
            root = root->left; // Search in the left subtree
        } else {
            root = root->right; // Search in the right subtree
        }
    }

    return "Not Found";
}


void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%s : %s\n", root->key, root->value);
        display(root->right);
    }
}

int optimalCost(int freq[], int i, int j) {
    int cost = 0;
    for (int k = i; k <= j; k++) {
        cost += freq[k];
    }
    return cost;
}

struct Node* constructOBSTUtil(char keys[][100], char values[][100], int freq[], int i, int j, int cost[][100], struct Node* dp[][100]) {
    if (i > j) {
        return NULL;
    }

    if (dp[i][j] != NULL) {
        // Return the result if already computed
        return dp[i][j];
    }

    int minCost = INT_MAX;
    int rootIndex = -1;

    for (int k = i; k <= j; k++) {
        if (cost[i][k - 1] + cost[k + 1][j] < minCost) {
            minCost = cost[i][k - 1] + cost[k + 1][j];
            rootIndex = k;
        }
    }

    freq[rootIndex]++;  // Update frequency for the selected key

    struct Node* root = newNode(keys[rootIndex], values[rootIndex]);
    root->left = constructOBSTUtil(keys, values, freq, i, rootIndex - 1, cost, dp);
    root->right = constructOBSTUtil(keys, values, freq, rootIndex + 1, j, cost, dp);

    dp[i][j] = root;  // Save the result in the DP table
    return root;
}

struct Node* constructOBST(char keys[][100], char values[][100], int freq[], int n) {
    int cost[n][n];
    struct Node* dp[n][n];

    memset(dp, 0, sizeof(dp));  // Initialize DP table with NULL

    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
        dp[i][i] = newNode(keys[i], values[i]);  // Base case: single node
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        optimalCost(freq, i, j);

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }

    return constructOBSTUtil(keys, values, freq, 0, n - 1, cost, dp);
}

int main() {
    struct Node* root = NULL;
    int n, i;
    char entry[256];
    char key[100], value[100];

    printf("Enter the number of entries in the dictionary: ");
    scanf("%d", &n);
    getchar(); // Consume the newline character

    int freq[n];
    memset(freq, 0, sizeof(freq));

    char keys[n][100];
    char values[n][100];

    printf("Enter the dictionary entries (English word : Indonesian word):\n");
    for (i = 0; i < n; i++) {
        fgets(entry, sizeof(entry), stdin);
        sscanf(entry, "%99[^:]:%99[^\n]", key, value);

        size_t len = strlen(value);
        if (len > 0 && value[len - 1] == '\n') {
            value[len - 1] = '\0';
        }

        strcpy(keys[i], key);
        strcpy(values[i], value);

        // Call the updated insert function
        root = insert(root, key, value);
    }

    printf("\nOptimal Binary Search Tree:\n");
    display(root);

    printf("\nEnter the English word to search (type 'exit' to stop): ");
    while (1) {
        fgets(key, sizeof(key), stdin);

        size_t len = strlen(key);
        if (len > 0 && key[len - 1] == '\n') {
            key[len - 1] = '\0';  // Remove the newline character
        }

        if (strcmp(key, "exit") == 0) {
            break;
        }

        printf("Searching for: %s\n", key);  // Add this line for debugging

        char* result = search(root, key);
        printf("Translation: %s\n", result);

        printf("\nEnter the English word to search (type 'exit' to stop): ");
    }

    return 0;
}
