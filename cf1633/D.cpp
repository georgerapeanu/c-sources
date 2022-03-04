#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int VMAX = 1e3;
const int KMAX = 1e6;

int t;
int n, k;
int b[NMAX + 5];
int c[NMAX + 5];
int cost[NMAX + 5];

int main(){

  for(int i = 1;i <= VMAX;i++){
    cost[i] = VMAX + 5;
  }

  cost[1] = 0;

  int max_individual_cost = 0;

  for(int i = 1;i <= VMAX;i++){
    for(int d = 1;d <= i;d++){
      cost[i + i / d] = min(cost[i + i / d], cost[i] + 1);
    }
    max_individual_cost = max(max_individual_cost, cost[i]);
  }
   
  vector<int> dp(NMAX * max_individual_cost + 5, 0);

  scanf("%d", &t);

  while(t--){
    scanf("%d %d", &n, &k);

    for(int i = 1;i <= n;i++){
      scanf("%d", &b[i]);
    }
    
    for(int i = 1;i <= n;i++){
      scanf("%d", &c[i]);
    }

    for(auto &it:dp){
      it = 0;
    }

    for(int i = 1;i <= n;i++){
      for(int j = min(max_individual_cost * (i - 1), k);j >= 0;j--){
        if(j + cost[b[i]] < (int)dp.size()){
          dp[j + cost[b[i]]] = max(dp[j + cost[b[i]]], dp[j] + c[i]);
        }
      }
      for(int j = 1;j <= k && j <= max_individual_cost * i;j++){
        dp[j] = max(dp[j - 1], dp[j]);
      }
    }

    printf("%d\n", dp[min(k, max_individual_cost * n)]);
  }

  return 0;
}
