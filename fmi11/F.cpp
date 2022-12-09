#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main(){
  
  int a, b;
  scanf("%d %d", &a, &b);
  vector<vector<int> > dp(a + 1, vector<int> (b + 1, 0));

  dp[0][0] = 1;

  for(int i = 0;i <= a;i++){
    for(int j = 0;j <= b;j++){
      dp[i][j] += (i >= 2 ? dp[i - 2][j]:0);
      dp[i][j] %= MOD;
      dp[i][j] += (i >= 3 ? dp[i - 3][j]:0);
      dp[i][j] %= MOD;
      dp[i][j] += (j >= 2 ? dp[i][j - 2]:0);
      dp[i][j] %= MOD;
      dp[i][j] += (j >= 3 ? dp[i][j - 3]:0);
      dp[i][j] %= MOD;
    }
  }
  
  printf("%d\n", dp[a][b]);

  return 0;
}
