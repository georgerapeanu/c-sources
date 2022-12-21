#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

bool banned(int x, int y){
  if(abs(x - y) == 1 && (x >> 1) == (y >> 1)){
    return true;
  }
  return false;
}

int main(){
  ios::sync_with_stdio(true);
  cin.tie(0);
  cout.tie(0);
    
  int n;

  cin >> n;

  vector<pair<int, int>> costs(2 * n);

  for(int i = 0;i < 2 * n;i++){
    cin >> costs[i].first;
    costs[i].second = i;
  }

  sort(costs.begin(), costs.end());
//  dbg(costs);
  vector<long long> pref(2 * n, 0);
  
  for(int i = 0;i < 2 * n;i++){
    pref[i] = (i > 0 ? pref[i - 1]:0) + (i % 2 == 1 ? -costs[i].first:costs[i].first);
  }

  vector<long long> dp(2 * n, 1e18);

  for(int i = 1;i < 2 * n;i += 2){
    if(banned(costs[0].second, costs[i].second) && i == 1){
      continue;
    }
    dp[i] = (costs[i].first - costs[0].first) + (pref[i - 1] - pref[0]);
  }


  vector<pair<long long, int> > candidates;

  for(int i = 1;i < 2 * n;i += 2){
    for(auto it:candidates){
      if(banned(costs[it.second + 1].second, costs[i].second) && i - it.second == 2){
        continue;
      }
//      dbg(i, dp[i], it.first, costs[i].second, pref[i - 1], costs[it.second + 1].second, costs[i].second);
      dp[i] = min(dp[i], it.first + costs[i].first + pref[i - 1]);
    }
    candidates.push_back({dp[i] - costs[i + 1].first - pref[i + 1],i});
    sort(candidates.begin(), candidates.end());
    candidates.resize(min(candidates.size(), (size_t)2));
    //dbg(i, candidates, dp[i]);
  }

  cout << dp[2 * n - 1];

  return 0;
}
