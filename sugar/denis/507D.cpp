#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1000;
const int KMAX = 100;
const int SIGMA = 10;

int n,k,mod;
int total_dp[NMAX + 5];
int dp[NMAX + 5][KMAX + 5];
int pw10[NMAX + 5];
int cf_pw10[NMAX + 5];

int main() {

    scanf("%d %d %d",&n,&k,&mod);

    pw10[0] = 1;
    cf_pw10[0] = 1;
    for(int i = 1; i <= n; i++) {
        pw10[i] = 1LL * SIGMA * pw10[i - 1] % mod;
        cf_pw10[i] = 1LL * SIGMA * cf_pw10[i - 1] % k;
    }

    for(int i = 1; i <= n; i++) {
        for(int cf = 1; cf < SIGMA; cf++) {
            int wh = 1LL * cf_pw10[i - 1] * cf % k;
            dp[i][wh]++;
            if(dp[i][wh] >= mod) {
                dp[i][wh] -= mod;
            }
        }
        total_dp[i] += dp[i][0];
        if(total_dp[i] >= mod) {
            total_dp[i] -= mod;
        }
        for(int j = 1; j < k; j++) {
            if(dp[i][j] == 0) {
                continue;
            }
            for(int cf = 0; cf < SIGMA; cf++) {
                int wh = (j + 1LL * cf * cf_pw10[i]) % k;
                dp[i + 1][wh] += dp[i][j];
                if(dp[i + 1][wh] >= mod) {
                    dp[i + 1][wh] -= mod;
                }
            }
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int delta = total_dp[i];
        if(i < n) {
            delta = 1LL * delta * pw10[n - i - 1] % mod;
            delta = 1LL * delta * (SIGMA - 1) % mod;
        }
        ans += delta;
        if(ans >= mod) {
            ans -= mod;
        }
    }

    printf("%d\n",ans);

    return 0;
}

