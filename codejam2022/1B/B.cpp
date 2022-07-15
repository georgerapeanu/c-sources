#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    int n, p;
    scanf("%d %d", &n, &p);

    vector<pair<int,int> > range(n + 1, make_pair(1e9+1,-1e9-1));

    range[0] = make_pair(0,0);
    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= p;j++){
        int value;
        scanf("%d", &value);
        range[i].first = min(range[i].first, value);
        range[i].second = max(range[i].second, value);
      }
    }
    
    vector<vector<long long> > dp(n + 1, vector<long long>(2, 0));

    for(int i = 1;i <= n;i++){
      dp[i][0] = (range[i].second - range[i].first) + min(dp[i - 1][0] + abs(range[i].second - range[i - 1].first), dp[i - 1][1] + abs(range[i].second - range[i - 1].second));
      dp[i][1] = (range[i].second - range[i].first) + min(dp[i - 1][0] + abs(range[i].first - range[i - 1].first), dp[i - 1][1] + abs(range[i].first - range[i - 1].second));
    }

    printf("Case #%d: %lld\n", test, min(dp[n][0], dp[n][1]));
  }

  return 0;
}
