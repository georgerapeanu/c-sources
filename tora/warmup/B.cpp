#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++) {
    int n;
    scanf("%d", &n);

    vector<int> v(n, 0);

    for(auto &it:v){
      scanf("%d", &it);
    }
    vector<vector<int> > dp(n, vector<int>(2, 0));

    dp[0] = {0, -v[0]};
    for(int i = 1;i < (int)v.size();i++){
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + v[i]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - v[i]);
    }


    printf("SHOW #%d: %d\n", test, dp[(int)v.size() - 1][0]);
  }
  
  return 0;
} 
