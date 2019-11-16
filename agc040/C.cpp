#include <bits/stdc++.h>

using namespace std;

const int MOD = 988244353;
const int NMAX = 1e7;

int n;

int lgpow(int base,int exp) {
    int ans = 1;
    while(exp) {
        if(exp & 1) {
            ans = 1LL * ans * base % MOD;
        }
        base = 1LL * base * base % MOD;
        exp >>= 1;
    }
    return ans;
}

int n;
int dp[100][2];

int main() {

    scanf("%d",&n);

    dp[0][0] = 1;
    dp[0][1] = 1;

    for(int i = 1; i <= n; i++) {
        dp[i][0] = (dp[i - 1][1] + (i > 1 ? dp[i - 2][0]:0));
        dp[i][1] = (dp[i - 1][0] + (i > 1 ? dp[i - 2][1]:0));
    }

    int ans = lgpow(9,n);

    return 0;
}
