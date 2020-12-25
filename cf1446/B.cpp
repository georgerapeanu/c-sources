#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e3;
const int MMAX = 5e3;

int dp[NMAX + 5][MMAX + 5];
int n,m;
string s;
string t;

int main(){

    cin >> n >> m;
    cin >> s;
    cin >> t;

    s = " " + s;
    t = " " + t;

    for(int i = 0;i <= n;i++){
        dp[i][0] = 0;
    }
    
    for(int j = 0;j <= m;j++){
        dp[0][j] = 0;
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            dp[i][j] = max(dp[i][j],dp[i - 1][j] - 1);
            dp[i][j] = max(dp[i][j],dp[i][j - 1] - 1);
            if(s[i] == t[j]){
                dp[i][j] = max(dp[i][j],2 + dp[i - 1][j - 1]);
            }
        }
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            ans = max(ans,dp[i][j]);
        }
    }

    cout << ans << "\n";

    return 0;
}
