#include <bits/stdc++.h>

using namespace std;

using dp_type=long long;
const dp_type inf = 1e18;

int main() {
  int t;
  cin >> t;

  while(t--) {
    int n, k;
    cin >> n >> k;

    vector<int> v(n + 1, 0);

    int vmax = -1e9;

    for(int i = 1; i <= n; i++) {
      cin >> v[i];
      vmax = max(vmax, v[i]);
    }

    vector<vector<vector<dp_type> > > dp(2, vector<vector<dp_type> > (k + 1, vector<dp_type>(vmax + k + 1, inf)));
    
    for(int j = 0;j <= k;j++){
      dp[1][j][v[1] + j] = 0;
    }
    
    for(int i = 1, h = 1;i < n;i++, h ^= 1){
      for(int j = 0;j <= k;j++){
        for(int l = 0;l <= vmax + k;l++){
          dp[1 - h][j][l] = inf;
        }
      }
      for(int j = 0;j <= k;j++){
        for(int l = v[i];l <= v[i] + k;l++){
          if(dp[h][j][l] == inf){
            continue;
          }
          for(int increase = 0;j + increase <= k;increase++){
            dp[1 - h][j + increase][v[i + 1] + increase] = min(dp[1 - h][j + increase][v[i + 1] + increase], dp[h][j][l] + abs(l - (v[i + 1] + increase)));
          }
        }
      }
    }

    dp_type ans = inf;

    for(int j = 0;j <= k;j++){
      for(int l = v[n];l <= v[n] + k;l++){
        ans = min(ans, dp[n & 1][j][l]);
      }
    }
    cout << ans << "\n";
  }

  return 0;
}
