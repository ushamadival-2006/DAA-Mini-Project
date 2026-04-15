#include <stdio.h>
#include <string.h>

#define MAX 100

void longestPalindromeSubseq(char str[]) {
    int n = strlen(str);
    int dp[MAX][MAX];

    // Base case
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    // Fill DP table
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;

            if (str[i] == str[j] && len == 2)
                dp[i][j] = 2;
            else if (str[i] == str[j])
                dp[i][j] = 2 + dp[i + 1][j - 1];
            else
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1]) ? dp[i + 1][j] : dp[i][j - 1];
        }
    }

    printf("\nLength of LPS: %d\n", dp[0][n - 1]);

    // Reconstruct LPS
    int i = 0, j = n - 1;
    char lps[MAX];
    int start = 0, end = dp[0][n - 1] - 1;

    while (i <= j) {
        if (str[i] == str[j]) {
            lps[start] = str[i];
            lps[end] = str[j];
            start++;
            end--;
            i++;
            j--;
        } else if (dp[i + 1][j] > dp[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }

    lps[dp[0][n - 1]] = '\0';

    printf("LPS: %s\n", lps);
}

int main() {
    char str[MAX];

    printf("Enter string: ");
    scanf("%s", str);

    longestPalindromeSubseq(str);

    return 0;
}