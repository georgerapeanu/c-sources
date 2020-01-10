#include <bits/stdc++.h>

using namespace std;

int n;
int dp[105][105][2];
int v[105];
bool ok[105];

int main() {


    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        ok[v[i]] = true;
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = 2000;
        }
    }

    if(v[1] == 0) {
        dp[1][0][0] = 0;
        dp[1][1][1] = 0;
    }
    else {
        dp[1][0][v[1] % 2] = 0;
    }

    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if(v[i] == 0) {
                dp[i][j][0] = min(dp[i - 1][j][0],dp[i - 1][j][1] + 1);
                if(j > 0 ) {
                    dp[i][j][1] = min(dp[i - 1][j - 1][0] + 1,dp[i - 1][j - 1][1]);
                }
                else {
                    dp[i][j][1] = 2000;
                }
            }
            else {
                dp[i][j][1 - (v[i] & 1)] = 200;
                dp[i][j][v[i] & 1] = min(dp[i - 1][j][0] + (v[i] % 2 != 0),dp[i - 1][j][1] + (v[i] % 2 != 1));
            }
        }
    }

    int tmp = 0;

    for(int i = 1; i <= n; i += 2) {
        tmp += (ok[i] == false);
    }

    printf("%d\n",min(dp[n][tmp][0],dp[n][tmp][1]));


    return 0;
}
