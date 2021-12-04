#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int n;
string s;
int dp[NMAX + 5][2];

int main(){

  cin >> n;
  cin >> s;

  s = " " + s;


  for(int i = 1;i <= n;i++){
    dp[i][0] = dp[i - 1][0] + (s[i] != 'A');
    dp[i][1] = dp[i - 1][1] + (s[i] != 'B');
    dp[i][0] = min(dp[i][0],dp[i][1] + 1);
    dp[i][1] = min(dp[i][1],dp[i][0] + 1);
  }

  cout << dp[n][0];

   return 0;
}
