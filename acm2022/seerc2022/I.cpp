#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

int main(){
  ios::sync_with_stdio(true);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vector<int> v(n, 0);

  for(auto &it:v){
    cin >> it;
  }

  vector<long long> dp(n, 0);

  for(int i = 0;i < n;i++){
    dp[i] = (i == 0 ? 0:dp[i - 1]) + v[i];
    if(i >= 1){
      dp[i] = min(dp[i], max(v[i - 1], v[i]) + (i - 2 < 0 ? 0:dp[i - 2]));
    }
    if(i >= 3){
      if(max(v[i - 2], v[i - 1]) >= max(v[i - 3], v[i])){
        dp[i] = min(dp[i], (max(v[i - 2], v[i - 1]) - max(v[i - 3], v[i])) + max(v[i], v[i - 3]) * 2 + (i < 4 ? 0:dp[i - 4]));
      }
      if(max(v[i - 2], v[i - 1]) >= min(v[i - 3], v[i])){
        dp[i] = min(dp[i], (max(v[i - 2], v[i - 1]) - min(v[i - 3], v[i])) + max(v[i], v[i - 3]) + min(v[i], v[i - 3]) + (i < 4 ? 0:dp[i - 4]));
      }
    }
  }

  cout << dp[n - 1];
  return 0;
}
