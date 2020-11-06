#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

char s[3005];
char t[3005];
int n,m;


///dp[i][j] = the number of ways that the current preffix of a will occupy t[i...j] in the final string.
///to update, we just iterate with l through s's letters, and if we look more carefully there are o(m) states to update
///the ones who are of length l, but didn't reach the end of t. they could be expanded either by adding a character in the front or in the back and every operation expands them
///and the ones who reached the end of t, because we can choose to put a character in the back and it doesnt matter
///we need dp[m + 1][m] with the meaning that we are going to achieve the preffix through front pushes only and none of the current characters will end up in the preffix
int dp[3005][3005];

int add(int a,int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}

int mult(int a,int b) {
    return 1LL * a * b % MOD;
}

int main() {

    fgets(s + 1,3005,stdin);
    fgets(t + 1,3005,stdin);


    n = strlen(s + 1);
    n -= (s[n] == '\n');
    m = strlen(t + 1);
    m -= (t[m] == '\n');

    for(int i = 1; i <= m; i++) {
        if(t[i] == s[1]) {
            dp[i][i] = 2;
        }
    }

    dp[m + 1][m] = 2;

    int ans = dp[1][m];

    for(int i = 1; i < n; i++) {
        ///the ones who reached m, so you can dump stuff there

        for(int j = 1; j <= m + 1; j++) {
            if(j > 1 && s[i + 1] == t[j - 1]) {
                dp[j - 1][m] = add(dp[j][m],dp[j - 1][m]);
            }
            if(j == m + 1) {
                dp[j][m] = add(dp[j][m],dp[j][m]);
            }
        }
        ///completely incased ones
        for(int j = 1; j + i - 1 < m; j++) {
            int k = j + i - 1;
            if(s[i + 1] == t[k + 1]) {
                dp[j][k + 1] = add(dp[j][k + 1],dp[j][k]);
            }
            if(j > 1 && s[i + 1] == t[j - 1]) {
                dp[j - 1][k] = add(dp[j - 1][k],dp[j][k]);
            }
            dp[j][k] = 0;
        }
        ans = add(ans,dp[1][m]);
    }

    printf("%d\n",ans);

    return 0;
}
