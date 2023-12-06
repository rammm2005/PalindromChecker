#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char word[50];
    char translation[50];
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char word[], char translation[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    strcpy(newNode->translation, translation);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* buildOptimalBST(char words[][50], char translations[][50], int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    Node* root = createNode(translations[mid], words[mid]);

    root->left = buildOptimalBST(words, translations, start, mid - 1);
    root->right = buildOptimalBST(words, translations, mid + 1, end);

    return root;
}

char* searchTranslation(Node* root, char word[]) {
    if (root == NULL || strcmp(root->word, word) == 0) {
        return (root == NULL) ? "Kata tidak ditemukan" : root->translation;
    }

    if (strcmp(word, root->word) < 0) {
        return searchTranslation(root->left, word);
    } else {
        return searchTranslation(root->right, word);
    }
}

void printInorder(Node* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%s: %s\n", root->word, root->translation);
        printInorder(root->right);
    }
}

int main() {
    char words[][50] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    char translations[][50] = {"apel", "pisang", "ceri", "kurma", "jeruk", "buah tin", "anggur"};

    int n = sizeof(words) / sizeof(words[0]);

    // Sorting words
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                char tempWord[50];
                char tempTranslation[50];

                strcpy(tempWord, words[i]);
                strcpy(tempTranslation, translations[i]);

                strcpy(words[i], words[j]);
                strcpy(translations[i], translations[j]);

                strcpy(words[j], tempWord);
                strcpy(translations[j], tempTranslation);
            }
        }
    }

    // Building optimal BST
    Node* root = buildOptimalBST(words, translations, 0, n - 1);

    // Displaying the dictionary
    printf("Kamus:\n");
    printInorder(root);

    // Translation choice
    int choice;
    printf("\nPilih jenis terjemahan:\n");
    printf("1. Bahasa Indonesia ke Bahasa Inggris\n");
    printf("2. Bahasa Inggris ke Bahasa Indonesia\n");
    scanf("%d", &choice);

    // Translation
    char searchWord[50];
    printf("\nMasukkan kata yang ingin dicari: ");
    scanf("%s", searchWord);

    char* translation;
    if (choice == 1) {
        translation = searchTranslation(root, searchWord);
        printf("Terjemahan: %s\n", translation);
    } else if (choice == 2) {
        // Invert the tree to translate from English to Indonesian
        Node* invertedRoot = NULL;
        invertedRoot = buildOptimalBST(translations, words, 0, n - 1);
        translation = searchTranslation(invertedRoot, searchWord);
        printf("Terjemahan: %s\n", translation);
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
