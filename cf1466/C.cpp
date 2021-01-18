#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 28;

int dp[100005][4];

int main(){

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    int t;

    cin >> t;

    while(t--){
        string s;

        cin >> s;

        int n = s.size();

        s = " " + s;

        dp[0][0] = 0;
        dp[0][1] = dp[0][2] = dp[0][3] = INF;

        for(int i = 1;i <= n;i++){
            for(int conf = 0;conf < 4;conf++){
                dp[i][conf] = INF;
                if(conf == 0 && s[i - 1] == s[i]){
                    continue;
                }
                if(i < 2 || s[i] != s[i - 2] || (s[i] == s[i - 2] && conf % 2 == 1)){
                    dp[i][conf] = (conf % 2) + min(dp[i][conf] - (conf % 2),dp[i - 1][0 | (conf >> 1)]);
                    dp[i][conf] = (conf % 2) + min(dp[i][conf] - (conf % 2),dp[i - 1][2 | (conf >> 1)]);
                }
                else{
                    dp[i][conf] = (conf % 2) + min(dp[i][conf] - (conf % 2),dp[i - 1][2 | (conf >> 1)]);
                }
            }
        }

        int ans = INF;

        for(int conf = 0;conf < 4;conf++){
            ans = min(ans,dp[n][conf]);
        }

        printf("%d\n",ans);
    }

    return 0;
}
