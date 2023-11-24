#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int n, int weights[], int values[], int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (weights[i - 1] <= j)
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    int selected_items[n];
    int count = 0;
    for (int i = n, j = capacity; i > 0 && j > 0; i--) {
        if (dp[i][j] != dp[i - 1][j]) {
            selected_items[count++] = i - 1;
            j -= weights[i - 1];
        }
    }

    printf("Maximum value: %d\nSelected items: ", dp[n][capacity]);
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", selected_items[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weights[n];
    int values[n];
    int capacity;

    for (int i = 0; i < n; i++) {
        printf("Enter weight and value for item %d: ", i + 1);
        scanf(" %d %d", &weights[i], &values[i]);  
    }

    printf("Enter the knapsack capacity: ");
    scanf("%d", &capacity);

    knapsack(n, weights, values, capacity);

    return 0;
}
