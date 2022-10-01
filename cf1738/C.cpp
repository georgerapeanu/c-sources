#include <bits/stdc++.h>

using namespace std;


int dp[101][101][2][2]; ///dp[i][j][k][l] -> i evens j odds, k's turn and alice has l sum

int main(){
  
  int t;

  scanf("%d", &t);

  dp[0][0][0][0] = 1;
  dp[0][0][1][0] = 1;
  dp[0][0][0][1] = 0;
  dp[0][0][1][1] = 0;

  for(int i = 0;i <= 100;i++){
    for(int j = 0;j <= 100;j++){
      if(i == 0 && j == 0){
        continue;
      }
      for(int k = 0;k < 2;k++){
        for(int l = 0;l < 2;l++){
          if(i == 0){
            dp[i][j][k][l] = dp[i][j - 1][k ^ 1][l ^ (k == 0)];
          } else if(j == 0){
            dp[i][j][k][l] = dp[i - 1][j][k ^ 1][l];
          } else if(k == 0){
            dp[i][j][k][l] = max(dp[i][j - 1][k ^ 1][l ^ (k == 0)], dp[i - 1][j][k ^ 1][l]);
          } else {
            dp[i][j][k][l] = min(dp[i][j - 1][k ^ 1][l ^ (k == 0)], dp[i - 1][j][k ^ 1][l]);
          }
        }
      }
    }
  }

  while(t--){
    int n;
    int fr[] = {0, 0};
    scanf("%d", &n);
    
    while(n--){
      int value;
      scanf("%d", &value);
      fr[value & 1]++;
    }

    printf(dp[fr[0]][fr[1]][0][0] ? "Alice\n":"Bob\n");

  }

  return 0;
}
