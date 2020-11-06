#include <bits/stdc++.h>

using namespace std;

int n,m;

int dp[305][305];
string s;
string t;

int main() {
    cin >> n >> m;
    cin >> s;
    cin >> t;

    s = " " + s;
    t = " " + t;

    for(int i = m; i; i--) {
        for(int j = 1; j <= n; j++) {
            if(s[j] != t[i]) {
                dp[i][j] = 1e9;
            }
            else {
                dp[i][j] = 1e9;
                if(i == m) {
                    dp[i][j] = min(dp[i][j],0);
                }
                if(j > 1) {
                    dp[i][j] = min(dp[i][j],1 + dp[i + 1][j - 1]);
                }
                if(j < n) {
                    dp[i][j] = min(dp[i][j],1 + dp[i + 1][j + 1]);
                }
            }
        }
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                if(s[j] == s[k]) {
                    dp[i][j] = min(dp[i][j],dp[i][k] + abs(j - k));
                }
            }
        }
    }

    int ans = 1e9;

    for(int i = 1; i <= n; i++) {
        ans = min(ans,dp[1][i]);
    }

    ans = (ans >= 1e9 ? -1:ans);

    cout << ans;

    return 0;
}

