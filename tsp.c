#include <stdio.h>
#include <limits.h>

#define MAX 20

int n;
int cost[MAX][MAX];
int dp[1 << MAX][MAX];  // DP table

// Function to find minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// TSP function using recursion + memoization
int tsp(int mask, int pos) {

    // ✅ Base case: all cities visited
    if (mask == (1 << n) - 1) {
        return cost[pos][0];  // return to starting city
    }

    // ✅ If already computed
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    // Try visiting all unvisited cities
    for (int city = 0; city < n; city++) {

        // If city is not visited
        if ((mask & (1 << city)) == 0) {

            int newAns = cost[pos][city] +
                         tsp(mask | (1 << city), city);

            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    // Initialize DP array with -1
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    // Start from city 0 with mask = 1 (only city 0 visited)
    int result = tsp(1, 0);

    printf("\nMinimum travelling cost: %d\n", result);

    return 0;
}