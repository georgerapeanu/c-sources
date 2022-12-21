#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;
  string s;
  cin >> n;
  cin >> s;
  
  int t;
  map<char, int> cost;

  cin >> t;

  int best_cost = -1;
  for(int i = 1;i <= t;i++){
    char c;
    int v;
    cin >> c >> v;
    cost[c] = v;
    if(best_cost < v){
      best_cost = v;
    }
  }

  if(n == 1){
    cout << (s[0] == '?' ? best_cost:cost[s[0]]);
    return 0;
  }

  int p = n;
  for(int i = 2;1LL * i * i <= n;i++){
    if(n % i == 0){
      p = i;
      break;
    }
  }

  vector<long long> dp(n, 0);
  int layers = 0;

  for(int current_power = n;current_power;current_power /= p){
    layers++;
    vector<long long> old_dp;
    old_dp.swap(dp);
    dp = vector<long long>(n, 0);
    for(int i = 0;i < current_power;i++){
      char activeChar = -1;
      bool is_impossible = false;
      for(int j = i;j < n;j += current_power){
        dp[i] += old_dp[j];
        if(s[j] != '?'){
          if(activeChar == -1 || activeChar == s[j]){
            activeChar = s[j];
          } else {
            is_impossible = true;
          }
        }
      }
      if(is_impossible){
        continue;
      }
      int target_cost = (activeChar == -1 ? best_cost:cost[activeChar]);
      dp[i] = max(dp[i], 1LL * (n / current_power) * target_cost * layers);
    }
  }

  cout << dp[0];

  return 0;
}
