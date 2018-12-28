#include <iostream>

using namespace std;

const int NMAX = 1e5;
int n;
string s;
long long dp[NMAX + 5][5];
int a[NMAX + 5];

const string cv = "#hard";

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> n >> s;
    s = " " + s;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }    
   
    for(int i = 0;i <= n;i++){
        for(int j = 0;j < 5;j++){
            dp[i][j] = 1LL << 62;
        }
    }

    dp[0][0] = 0;

    for(int i = 1;i <= n;i++){
       dp[i][0] = (s[i] == 'h' ? a[i] + dp[i - 1][0]:dp[i - 1][0]);
       for(int j = 1;j < 5;j++){
            dp[i][j] = dp[i - 1][j] + a[i];
            if(j < 4 && cv[j + 1] != s[i]){
                 dp[i][j] = min(dp[i][j],dp[i - 1][j]); 
            } 
            if(s[i] == cv[j]){
                dp[i][j] = min(dp[i][j],dp[i - 1][j - 1]);
            }
       }
     // for(int j = 0;j < 5;j++){
      //  cout << dp[i][j] << " ";
     // } 
     // cout << "\n";
    }

    long long ans = 1LL << 62;

    for(int j = 0;j < 4;j++){
        ans = min(ans,dp[n][j]);
    }

    cout << ans;

    return 0;
}
