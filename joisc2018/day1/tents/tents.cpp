#include <cstdio>
#include <algorithm>

using namespace std;

const int XMAX = 3000;
const int MOD = 1e9 + 7;

int dp[XMAX + 5][XMAX + 5];

int main() {

    for(int i = 0; i <= XMAX + 2; i++) {
        dp[i][0] = dp[0][i] = 1;
    }

    int h,w;

    scanf("%d %d",&h,&w);

    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] = (dp[i][j] + 4LL * dp[i - 1][j - 1] * j) % MOD;
            if(j > 1)dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][j - 2] * j * (j - 1) / 2) % MOD;
            if(i > 1)dp[i][j] = (dp[i][j] + 1LL * dp[i - 2][j - 1] * j * (i - 1)) % MOD;
        }
    }

    printf("%d\n",(dp[h][w] == 0 ? MOD - 1:dp[h][w] - 1));

    return 0;
}
