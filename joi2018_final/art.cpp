#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int n;

  scanf("%d", &n);

  vector<pair<long long, int> > v(n, {0, 0});
  vector<long long> dp(n, 0);

  for(auto &it:v){
    scanf("%lld %d", &it.first, &it.second);
  }

  sort(v.begin(), v.end());
  
  long long ans = 0;
  for(int i = 0;i < n;i++){
    dp[i] = max(1LL * v[i].second, (i == 0 ? 0LL:v[i].second - (v[i].first - v[i - 1].first) + dp[i - 1]));
    ans = max(ans, dp[i]);
  }
  printf("%lld\n", ans);

  return 0;
}

