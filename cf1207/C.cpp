#include <bits/stdc++.h>

using namespace std;

const long long naspa = 1LL << 60;

int t;
int n;
int a,b;
string s;
long long dp[int(2e5) + 5][2];

int main() {

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> t;

    while(t--){
        cin >> n >> a >> b;
        cin >> s;
        int cnt = 0;
        dp[0][0] = b;
        dp[0][1] = naspa;

        for(int i = 0;i < n;i++){
            if(s[i] == '0'){
                dp[i + 1][0] = min(dp[i][0] + a + b,dp[i][1] + 2 * a +  b);
                dp[i + 1][1] = min(dp[i][0] + 2 * a + 2 * b,dp[i][1] + a + 2 * b);
            }
            else{
                dp[i][0] = naspa;
                dp[i + 1][0] = naspa;
                dp[i + 1][1] = dp[i][1] + a + 2 * b;
            }
        }

        cout << dp[n][0] << "\n";
    }

    return 0;
}
