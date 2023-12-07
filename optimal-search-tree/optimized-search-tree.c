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

Node* insert(Node* root, char word[], char translation[]) {
    if (root == NULL) {
        return createNode(word, translation);
    }

    int compareResult = strcmp(word, root->word);

    if (compareResult < 0) {
        root->left = insert(root->left, word, translation);
    } else if (compareResult > 0) {
        root->right = insert(root->right, word, translation);
    }

    return root;
}

char* searchTranslation(Node* root, char word[], int choice) {
    if (root == NULL) {
        char* notFoundMessage = (char*)malloc(strlen("Kata tidak ditemukan") + 1);
        strcpy(notFoundMessage, "Kata tidak ditemukan");
        return notFoundMessage;
    }

    int compareResult;
    if (choice == 1) {
        compareResult = strcmp(word, root->word);
    } else if (choice == 2) {
        compareResult = strcmp(word, root->translation);
    } else {
        char* invalidChoiceMessage = (char*)malloc(strlen("Pilihan tidak valid.") + 1);
        strcpy(invalidChoiceMessage, "Pilihan tidak valid.");
        return invalidChoiceMessage;
    }

    if (compareResult == 0) {
        char* result = (char*)malloc(strlen((choice == 1) ? root->translation : root->word) + 1);
        strcpy(result, (choice == 1) ? root->translation : root->word);
        return result;
    } else if (compareResult < 0) {
        return searchTranslation(root->left, word, choice);
    } else {
        return searchTranslation(root->right, word, choice);
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
    Node* root = NULL;

    // Insert initial words and translations
    root = insert(root, "apple", "apel");
    root = insert(root, "banana", "pisang");
    root = insert(root, "cherry", "ceri");
    root = insert(root, "date", "kurma");
    root = insert(root, "elderberry", "jeruk");
    root = insert(root, "fig", "buah tin");
    root = insert(root, "grape", "anggur");

    // Displaying the dictionary
    printf("Kamus:\n");
    printInorder(root);

    // Translation choice
    int choice;
    printf("\n\nPilih jenis terjemahan:\n");
    printf("1. Bahasa Indonesia ke Bahasa Inggris\n");
    printf("2. Bahasa Inggris ke Bahasa Indonesia\n");
    scanf("%d", &choice);

    // Translation
    char searchWord[50];
    printf("\nMasukkan kata yang ingin dicari: ");
    getchar();  // Consume the newline character left in the buffer
    fgets(searchWord, sizeof(searchWord), stdin);
    searchWord[strcspn(searchWord, "\n")] = '\0';  // Remove the newline character

    char* translation = searchTranslation(root, searchWord, choice);
    printf("Terjemahan: %s\n", translation);

    // Inserting new word and translation
    char newWord[50], newTranslation[50];
    printf("\nMasukkan kata baru: ");
    scanf("%s", newWord);
    printf("Masukkan terjemahan kata baru: ");
    scanf("%s", newTranslation);

    root = insert(root, newWord, newTranslation);

    // Displaying the updated dictionary
    printf("\n\nKamus Baru:\n");
    printInorder(root);

    return 0;
}
