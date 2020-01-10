#include <fstream>

using namespace std;

ifstream f("zuma.in");
ofstream g("zuma.out");

string s;
int n,m;
int dp[505][505];
int ans[505];

int main() {

    f >> n >> m;
    f >> s;

    s = " " + s;

    for(int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }

    for(int l = 1; l < n; l++) {
        for(int i = 1; i + l <= n; i++) {
            int j = i + l;
            for(int k = i; k < j; k++) {
                if(dp[k + 1][j] >= m) {
                    dp[i][j] = max(dp[i][j],dp[i][k]);
                }
                if(s[i] == s[k + 1] && dp[i][k] && dp[k + 1][j]) {
                    dp[i][j] = max(dp[i][j],dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        ans[i] = 1 + ans[i - 1];
        for(int j = i; j; j--) {
            if(dp[j][i] >= m) {
                ans[i] = min(ans[i],ans[j - 1]);
            }
        }
    }

    g << ans[n];

    return 0;
}
