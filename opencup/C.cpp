#include <bits/stdc++.h>

using namespace std;

string s,t;

int n,m;

int dp[2005][2005];

int main(){

    while(cin >> s >> t){
        n = s.size();
        m = t.size();

        s = " " + s;
        t = " " + t;

        for(int i = 0;i <= m;i++){
            dp[n + 1][i] = m - i + 1;
        }
        for(int i = 0;i <= n;i++){
            dp[i][m + 1] = 0;
        }
        dp[n + 1][m + 1] = 0;
        
        for(int i = n;i;i--){
            for(int j = m;j;j--){
                dp[i][j] = 0;
                if(s[i] == t[j]){
                    dp[i][j] = max(2 + dp[i + 1][j + 1],max(dp[i + 1][j],dp[i][j + 1]));
                }
                else if(s[i] < t[j]){
                    dp[i][j] = (n - i + 1) + (m - j + 1);
                }
                else{
                    dp[i][j] = max(dp[i + 1][j],dp[i][j + 1]);
                }
            }
        }

        cout << dp[1][1] << "\n";
    }


    return 0;
}
