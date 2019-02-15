#include <cstdio>
#include <algorithm>

using namespace std;

const int inf = 1e9;

int n,m;
int fr[int(1e6) + 5];
int dp[int(1e6) + 5][7][7];

int main() {
    scanf("%d %d",&n,&m);
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        fr[val]++;
    }

    for(int i = 0; i <= m; i++) {
        for(int j = 0; j < 7; j++) {
            for(int k = 0; k < 7; k++) {
                dp[i][j][k] = -inf;
            }
        }
    }

    dp[0][0][0] = 0;

    for(int i = 1; i <= m + 3; i++) {
        for(int k = 0; k < 7; k++) {
            if(k > fr[i - 1]) {
                continue;
            }
            for(int l = 0; l <= k; l++) {
                if(l > fr[i]) {
                    continue;
                }
                for(int j = l; j <= (i < 2 ? 0:fr[i - 2]) && j < 7; j++) {
                    dp[i][k][l] = max(dp[i][k][l],dp[i - 1][j - l][k - l] + ((fr[i - 2] - j) / 3) + l);
                }
            }
        }
    }

    printf("%d\n",dp[m + 3][0][0]);
    return 0;
}
