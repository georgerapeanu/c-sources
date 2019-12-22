#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 5000;

int c,d,y;
int coef[1005];
long long dp[MOD + 5];

int per[MOD + 5],len_per = -1;

int get_dp(int pos) {
    return dp[pos % MOD];
}

int main() {

    scanf("%d %d %d",&c,&d,&y);

    for(int i = 1; i <= d; i++) {
        scanf("%d",&coef[i]);
        coef[i] = coef[i] + coef[i - 1];
    }

    for(int i = 1; i <= d; i++) {
        int p;
        scanf("%d",&p);
        coef[i] += c - p;
///        printf("%d ",coef[i]);
    }

///    printf("\n");

    for(int i = 1; i <= y; i++) {
        dp[i % MOD] = 1LL << 62;
        if(i <= 10 * d) {
            for(int j = max(0,i - d); j <= i; j++) {
                dp[i % MOD] = min(dp[i % MOD],dp[j % MOD] + coef[(i - j) % MOD]);
            }
        }
        else {
            if(len_per == -1) {
                for(int x = 2 * d; x > 0; x--) {
                    for(int j = i - x; j < i; j++) {
                        per[j % x] = get_dp(j) - get_dp(j - x);
                    }
                    bool ok = true;
                    for(int j = i - 2 * x; j < i - x; j++) {
                        ok &= (per[j % x] == get_dp(j) - get_dp(j - x));
                    }
                    if(ok) {
                        len_per = x;
                        break;
                    }
                }
            }
            dp[i % MOD] = get_dp(i - len_per) + per[i % len_per];
        }
        ///      if(i > d)printf("%d %d %d %d\n",i,dp[i % 2000],dp[(i - d) % 2000],dp[i % 2000] - dp[(i - d) % 2000]);
    }


    printf("%lld\n",dp[y % MOD]);

    return 0;
}
