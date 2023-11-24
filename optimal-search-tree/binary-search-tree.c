#include <stdio.h>
#include <limits.h>

float optimalBST(char keys[][10], float probs[], int n) {
    float cost[n + 1][n + 1];

    for (int i = 1; i <= n; i++) {
        cost[i][i] = probs[i - 1];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;

            for (int k = i; k <= j; k++) {
                float currentCost = ((k > i) ? cost[i][k - 1] : 0) +
                                    ((k < j) ? cost[k + 1][j] : 0) +
                                    probs[k - 1];

                cost[i][j] = (currentCost < cost[i][j]) ? currentCost : cost[i][j];
            }
        }
    }

    return cost[1][n];
}

int main() {
    int n;

    printf("Enter the number of keys: ");
    scanf("%d", &n);


    // Max Lenght is 10 char only
    char keys[n][10];  
    float probs[n];

    printf("Enter keys and their probabilities:\n");
    for (int i = 0; i < n; i++) {
        printf("Key %d: ", i + 1);
        scanf("%s", keys[i]);
        printf("Probability for key %d: ", i + 1);
        scanf("%f", &probs[i]);
    }

    float result = optimalBST(keys, probs, n);

    printf("The cost of the optimal binary search tree is: %f\n", result);

    return 0;
}
