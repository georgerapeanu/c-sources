#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;
const int LGMAX = 20;
const int MOD = 1e9 + 7;

int n;
int dp[2][LGMAX + 1][2];

int main() {
    scanf("%d",&n);

    int lg2 = 0;

    while((1 << lg2) <= n) {
        lg2++;
    }
    lg2--;

    dp[1][lg2][0] = 1;
    if(n >= 3 && (3 << (lg2 - 1) <= n)) {
        dp[1][lg2 - 1][1] = 1;
    }

    for(int i = 1,l = 1; i < n; i++,l ^= 1) {
        memset(dp[1 ^ l],0,sizeof(dp[1 ^ l]));
        for(int j = 0; j <= LGMAX; j++) {
            dp[1 ^ l][j][0] = (dp[1 ^ l][j][0] + 1LL * dp[l][j][0] * ((n / (1 << j)) - i)) % MOD;

            if(j > 0) {
                dp[1 ^ l][j - 1][0] = (dp[1 ^ l][j - 1][0] + 1LL * dp[l][j][0] * ((n / (1 << (j - 1))) - (n / (1 << j)))) % MOD;
            }

            dp[1 ^ l][j][1] = (dp[1 ^ l][j][1] + 1LL * dp[l][j][1] * ((n / (3 << j)) - i)) % MOD;

            if(j > 0) {
                dp[1 ^ l][j - 1][1] = (dp[1 ^ l][j - 1][1] + 1LL * dp[l][j][1] * ((n / (3 << (j - 1))) - (n / (3 << j)))) % MOD;
            }

            dp[1 ^ l][j][0] = (dp[1 ^ l][j][0] + 1LL * dp[l][j][1] * ((n / (1 << j)) - (n / (3 << j)))) % MOD;
        }
    }

    printf("%d\n",dp[n & 1][0][0]);

    return 0;
}
