#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const long long inf = 1e18;

int t,n;
long long dp[NMAX + 5][6];
int a[NMAX + 5];
int b[NMAX + 5];

int main() {

    scanf("%d",&t);

    while(t--) {

        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d %d",&a[i],&b[i]);
        }

        for(int k = 0; k < 6; k++) {
            dp[1][k] = 1LL * k * b[1];
        }

        for(int i = 2; i <= n; i++) {
            for(int k = 0; k < 6; k++) {
                dp[i][k] = inf;
                for(int l = 0; l < 6; l++) {
                    if(a[i - 1] + l != a[i] + k) {
                        dp[i][k] = min(dp[i][k],dp[i - 1][l] + 1LL *k * b[i]);
                    }
                }
            }
        }

        long long ans = inf;

        for(int k = 0; k < 6; k++) {
            ans = min(ans,dp[n][k]);
        }

        printf("%lld\n",ans);
    }

    return 0;
}
