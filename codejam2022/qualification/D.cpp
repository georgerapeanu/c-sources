#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    printf("Case #%d: ", test);
    int n;
    scanf("%d", &n);
    
    vector<int> f(n + 1, 0);
    vector<int> p(n + 1, 0);
    vector<vector<long long> > dp(n + 1, vector<long long>(2, 0));
    vector<long long> sum_dp1(n + 1, 0);
    vector<long long> best_upgrade(n + 1, -1e18);

    for(int i = 1;i <= n;i++){
      scanf("%d", &f[i]);
    }
    for(int i = 1;i <= n;i++){
      scanf("%d", &p[i]);
    }

    for(int i = n;i >= 0;i--){
      if(best_upgrade[i] == -1e18){
        best_upgrade[i] = 0;
      }

      dp[i][0] = sum_dp1[i] + best_upgrade[i];
      dp[i][1] = max(sum_dp1[i], sum_dp1[i] + best_upgrade[i] + f[i]);

      sum_dp1[p[i]] += dp[i][1];
      best_upgrade[p[i]] = max(best_upgrade[p[i]], dp[i][0] - dp[i][1]);
    }

    printf("%lld\n", dp[0][1]);
  }

  return 0;
}
