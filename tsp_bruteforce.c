#include <stdio.h>
#include <limits.h>

#define MAX 20

int n;
int cost[MAX][MAX];
int visited[MAX];
int minCost = INT_MAX;

// Function to find minimum
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Brute force TSP function
void tsp_bruteforce(int curr, int count, int costSoFar) {

    // If all cities visited and return path exists
    if (count == n && cost[curr][0]) {
        minCost = min(minCost, costSoFar + cost[curr][0]);
        return;
    }

    // Try all unvisited cities
    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[curr][i]) {

            visited[i] = 1;

            tsp_bruteforce(i, count + 1, costSoFar + cost[curr][i]);

            // Backtrack
            visited[i] = 0;
        }
    }
}

int main() {

    printf("\n--- Travelling Salesman Problem (Brute Force) ---\n");

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    // Initialize visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Start from city 0
    visited[0] = 1;
    tsp_bruteforce(0, 1, 0);

    printf("\nMinimum travelling cost (Brute Force): %d\n", minCost);

    return 0;
}