#include <stdio.h>
#include <stdlib.h>

// Deklarasi fungsi knapsack
void knapsack(int values[], int weights[], int n, int capacity, int *maxValue, int *totalWeight, int selectedItems[]);

int main() {
    int n;

    // Input jumlah barang
    printf("Masukkan jumlah barang: ");
    scanf("%d", &n);

    // Alokasi memori untuk arrays values, weights, dan selectedItems
    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));
    int *selectedItems = (int *)malloc(n * sizeof(int));

    if (values == NULL || weights == NULL || selectedItems == NULL) {
        fprintf(stderr, "Gagal melakukan alokasi memori.\n");
        return 1;
    }

    // Input nilai dan berat masing-masing barang
    printf("Masukkan nilai dan berat masing-masing barang:\n");
    for (int i = 0; i < n; i++) {
        printf("Barang %d:\n", i + 1);
        printf("Nilai: ");
        scanf("%d", &values[i]);
        printf("Berat: ");
        scanf("%d", &weights[i]);
        selectedItems[i] = 0; // Awalnya, belum ada barang yang dipilih
    }

    int capacity;
    // Input kapasitas knapsack
    printf("Masukkan kapasitas knapsack: ");
    scanf("%d", &capacity);

    int maxValue, totalWeight;

    // Panggil fungsi knapsack
    knapsack(values, weights, n, capacity, &maxValue, &totalWeight, selectedItems);

    // Tampilkan hasil
    printf("Nilai maksimum yang dapat dimasukkan ke dalam knapsack: %d\n", maxValue);

    // Tampilkan total berat barang yang dimasukkan ke dalam knapsack
    printf("Total berat barang yang dimasukkan ke dalam knapsack: %d\n", totalWeight);

    // Tampilkan kapasitas knapsack yang digunakan
    printf("Kapasitas knapsack yang digunakan: %d\n", capacity - (capacity - totalWeight));

    // Tampilkan barang-barang yang dimasukkan ke dalam knapsack
    printf("Barang-barang yang dimasukkan ke dalam knapsack:\n");
    for (int i = 0; i < n; i++) {
        if (selectedItems[i] == 1) {
            printf("Barang %d - Nilai: %d, Berat: %d\n", i + 1, values[i], weights[i]);
        }
    }

    // Bebaskan memori yang dialokasikan
    free(values);
    free(weights);
    free(selectedItems);

    return 0;
}

// Definisi fungsi knapsack
void knapsack(int values[], int weights[], int n, int capacity, int *maxValue, int *totalWeight, int selectedItems[]) {
    int i, w;
    int dp[n + 1][capacity + 1];

    // Mengisi tabel DP
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]]) > dp[i - 1][w] ? (values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Nilai maksimum yang dapat dimasukkan ke dalam knapsack
    *maxValue = dp[n][capacity];

    // Menghitung total berat barang yang dimasukkan
    *totalWeight = 0;
    w = capacity;
    for (i = n; i > 0 && *maxValue > 0; i--) {
        if (*maxValue != dp[i - 1][w]) {
            selectedItems[i - 1] = 1; // Menandai bahwa barang i dipilih
            *totalWeight += weights[i - 1];
            *maxValue -= values[i - 1];
            w -= weights[i - 1];
        }
    }
}