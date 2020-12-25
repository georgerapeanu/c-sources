#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int inv2 = MOD / 2 + 1;
const int NMAX = 2e5;

int n;
int dp[NMAX + 5];
int sumdp[2];

int pw2[NMAX + 5];
int inv_pw2[NMAX + 5];

int main(){

    pw2[0] = inv_pw2[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        pw2[i] = 1LL * 2 * pw2[i - 1] % MOD;
        inv_pw2[i] = 1LL * inv2 * inv_pw2[i - 1] % MOD;
    }

    dp[0] = 1;

    scanf("%d",&n);

    sumdp[0] = 1;

    for(int i = 1;i <= n;i++){
        dp[i] = 1LL * inv_pw2[i] * sumdp[1 - (i % 2)] % MOD;
        sumdp[i % 2] = (sumdp[i % 2] + 1LL * pw2[i] * dp[i]) % MOD;
    }

    printf("%d\n",dp[n]);

    return 0;
}
