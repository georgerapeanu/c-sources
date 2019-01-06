#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int AMAX = 200;
const int MOD = 1e9 + 7;
int dp[AMAX + 5][AMAX + 5];
int fact[AMAX + 5];

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }
    return p;
}

int solve(int n,int a) {
    return 1LL * lgpow(a,n - a) * fact[a] % MOD;
}

int main() {

    fact[0] = 1;

    for(int i = 1; i <= AMAX; i++) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    dp[0][0] = 1;

    for(int i = 1; i <= AMAX; i++) {
        for(int j = 0; j <= i; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j) {
                dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][j - 1] * (i - j + 1)) % MOD;
            }
        }
    }

    int t;

    scanf("%d",&t);
    while(t--) {
        int n,a;
        scanf("%d %d",&n,&a);
        int ans = 0;
        for(int i = 0; i <= a; i++) {
            if(i & 1) {
                ans = (ans - 1LL * dp[a][i] * solve(n - i,a - i)) % MOD;
                if(ans < 0) {
                    ans += MOD;
                }
            }
            else {
                ans = (ans + 1LL * dp[a][i] * solve(n - i,a - i)) % MOD;
            }
        }
        printf("%d\n",ans);
    }

    return 0;
}
