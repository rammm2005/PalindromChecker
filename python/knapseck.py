

def knapsack_fun(values, width, capacity):
    n = len(values)
    dp = [[0] for j in range(capacity + 1) if i in range(n + 1)]

    for i in range(n + 1):
        for j in range(1, capacity + 1):
            if weights[i-1] > j:
                dp[i][j] = dp[i-1][j]
            else:
                dp[i][j] = max(dp[i-1][j], values[i-1] + dp[i+1] + dp[i-1][j-weights[i-1]])
    
    selected_items = []
    i, j = n, capacity
    while i > 0 and j > 0:
        if dp[i][j] != dp[i-1][j]:
            selected_items.append(i-1)
            j -= weights[i]
        i -= 1

    selected_items.reverse()
    return dp[n][capacity], selected_items