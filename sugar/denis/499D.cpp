#include <cstdio>

using namespace std;

const int NMAX = 5e3;
const double eps = 1e-14;
double dp[NMAX + 5][NMAX + 5];

int n,k;
double p[NMAX + 5];
double np[NMAX + 5];
int t[NMAX + 5];

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d %d",&x,&t[i]);
        p[i] = x / 100.0;
        np[i] = (100 - x) / 100.0;
    }

    dp[0][0] = 1;

    for(int i = 0; i <= n; i++) {
        double prob = 1;
        for(int j = 1; j <= t[i + 1]; j++) {
            prob *= np[i + 1];
        }
        for(int j = i; j <= k; j++) {
            if(dp[i][j] < eps) {
                continue;
            }
            if(j < k) {
                dp[i][j + 1] += dp[i][j] * np[i];
                dp[i + 1][j + 1] += dp[i][j] * p[i + 1];
                if(j <= k - t[i + 1]) {
                    dp[i + 1][j + t[i + 1]] += dp[i][j] * prob;
                    if(j <= k - t[i + 1] - 1) {
                        dp[i + 1][j + t[i + 1] + 1] -= dp[i][j] * prob;
                    }
                }
            }
        }
    }

    double ans = 0;

    for(int i = 1; i < n; i++) {
        double prob = 1;
        for(int j = k; j > k - t[i + 1]; j--) {
            ans += i * dp[i][j] * prob;
            prob *= (1 - p[i + 1]);
        }
    }

    for(int j = 1; j <= k; j++) {
        ans += n * dp[n][j];
    }

    printf("%.9f\n",ans);

    return 0;
}
