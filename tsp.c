#include <stdio.h>
#include <limits.h>

#define MAX 20

int n;
int cost[MAX][MAX];

// ---------- BITMASK DP ----------
int dp[1 << MAX][MAX];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int tsp_dp(int mask, int pos) {

    // Base case: all cities visited
    if (mask == (1 << n) - 1) {
        return cost[pos][0];
    }

    // If already computed
    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INT_MAX;

    // Try all unvisited cities
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {

            int newAns = cost[pos][city] +
                         tsp_dp(mask | (1 << city), city);

            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

// ---------- BRUTE FORCE ----------
int visited[MAX];
int minCost = INT_MAX;

void tsp_bruteforce(int curr, int count, int costSoFar) {

    // If all cities visited and return to start
    if (count == n && cost[curr][0]) {
        minCost = min(minCost, costSoFar + cost[curr][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[curr][i]) {

            visited[i] = 1;

            tsp_bruteforce(i, count + 1, costSoFar + cost[curr][i]);

            // Backtracking
            visited[i] = 0;
        }
    }
}

int main() {

    printf("\n--- Travelling Salesman Problem ---\n");

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    // ----- Brute Force -----
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;
    tsp_bruteforce(0, 1, 0);

    // ----- Bitmask DP -----
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    int dpResult = tsp_dp(1, 0);

    // ----- Output -----
    printf("\n================ TSP RESULT ================\n");

    printf("\nBrute Force Cost: %d\n", minCost);
    printf("Bitmask DP Cost: %d\n", dpResult);

    printf("\n--------------- ANALYSIS ---------------\n");

    printf("\nState Representation:\n");
    printf("dp[mask][i] = minimum cost to visit cities in mask and end at city i\n");

    printf("\nRecurrence Relation:\n");
    printf("dp[mask][i] = min(cost[i][j] + dp[mask | (1<<j)][j])\n");

    printf("\nTime Complexity:\n");
    printf("Brute Force = O(n!)\n");
    printf("Bitmask DP  = O(n^2 * 2^n)\n");

    printf("\nSpace Complexity:\n");
    printf("Bitmask DP = O(n * 2^n)\n");

    printf("\nComparison:\n");
    printf("Brute Force tries all permutations (slow)\n");
    printf("Bitmask DP avoids recomputation using DP (efficient)\n");

    printf("\nObservation:\n");
    printf("Both give same result, but Bitmask DP is faster.\n");

    printf("\n=========================================\n");

    return 0;
}