#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int dp[NMAX + 5];

int main() {

    dp[0] = 2;
    dp[1] = 2;

    for(int i = 2; i <= NMAX; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }

    int n,m;
    scanf("%d %d",&n,&m);
    printf("%d ",(dp[n] + dp[m] - 2) % MOD);

    return 0;
}
