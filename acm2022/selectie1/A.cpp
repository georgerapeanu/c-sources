#include <bits/stdc++.h>

using namespace std;

int main(){

  int a, b;
  scanf("%d %d", &a, &b);

  vector<vector<int> > dp(a + 1, vector<int>(b + 1, 0));

  dp[0][0] = 0;

  int answer = 0;

  for(int i = 0;i <= a;i++) {
    for(int j = 0;j <= b;j++) {
      if(i > 0 && (j < 40 || i - 1 < 40)){
        dp[i][j] = max(dp[i][j], dp[i - 1][j] + (i - 1 >= 40 ? 2 :1));
      } 
      if(j > 0 && (i < 40 || j - 1 < 40)) {
        dp[i][j] = max(dp[i][j], dp[i][j - 1] + (i >= 40 ? 1:2));
      }
      if(i >= 40 && j >= 40 && (i <= 40 || j <= 40)){
        answer = max(answer, dp[i][j]);
      }
    }
  }

  printf("%d\n", answer);


  return 0;
}
