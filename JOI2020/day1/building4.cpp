#include <bits/stdc++.h>

using namespace std;

int n;
pair<int,int> dp[1000005][2];
int v[1000005][2];

int main() {

    scanf("%d",&n);

    for(int h = 0; h < 2; h++) {
        for(int i = 1; i <= 2 * n; i++) {
            scanf("%d",&v[i][h]);
        }
    }

    dp[1][0] = {0,0};
    dp[1][1] = {1,1};

    for(int i = 2; i <= 2 * n; i++) {
        for(int h = 0; h < 2; h++) {
            dp[i][h] = {1e9,0};
            for(int h2 = 0; h2 < 2; h2++) {
                if(v[i - 1][h2] <= v[i][h]) {
                    dp[i][h].first = min(dp[i][h].first,dp[i - 1][h2].first + h);
                    dp[i][h].second = max(dp[i][h].second,dp[i - 1][h2].second + h);
                }
            }
        }
    }

    for(int h = 0; h < 2; h++) {
        if(dp[n * 2][h].first <= n && n <= dp[n * 2][h].second) {
            int x = 2 * n,y = n;
            string ans(2 * n,' ');
            while(x) {
                ans[x - 1] = (h == 1) + 'A';
                y -= h;
                x--;
                if(v[x][0] <= v[x + 1][h] && dp[x][0].first <= y && y <= dp[x][0].second) {
                    h = 0;
                }
                else {
                    h = 1;
                }
            }
            cout << ans << endl;;
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}
