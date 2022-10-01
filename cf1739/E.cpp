#include <bits/stdc++.h>

using namespace std;

int get(string s[2], int i, int j){
  if(0 <= i && i < 2 && 0 <= j && j < (int)s[i].size()){
    return (s[i][j] == '1');
  }
  return 0;
}

int main(){
  
  int n;
  cin >> n;
  string s[2];
  cin >> s[0];
  cin >> s[1];

  vector<vector<int> > dp(2, vector<int>(n, 0));

  for(int j = n - 1;j >= 0;j--){
    for(int i = 0;i < 2;i++){
      if(j == n - 1){
        dp[i][j] = get(s, i, j) + get(s, i ^ 1, j);
      }else{
        if(s[i ^ 1][j] == '1'){
          if(s[i][j + 1] == '1'){
            dp[i][j] = get(s, i, j) + get(s, i ^ 1, j) + get(s, i ^ 1, j + 1) + (j + 2 < n ? dp[i ^ 1][j + 2]:0);
          }else{
            dp[i][j] = get(s, i, j) + get(s, i ^ 1, j) + dp[i ^ 1][j + 1];
          }
        }
        dp[i][j] = max(dp[i][j], get(s, i, j) + dp[i][j + 1]);
      }
    }
  }

  printf("%d\n", dp[0][0]);
  
  return 0;
}
