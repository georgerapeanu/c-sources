#include <bits/stdc++.h>

using namespace std;

int calc(vector<int> &dp, vector<int> &visited, int pos, int fact, int delta){
  if(visited[pos]) {
    return dp[pos];
  }
  visited[pos] = 1;
  dp[pos] = calc(dp, visited, (1LL * pos * fact + delta) % (int)dp.size(), fact, delta); 
  if(dp[pos] != -1){
    dp[pos]++;
  }
  return dp[pos];
}


int main(){

  int n, k;
  cin >> n >> k;

  int len_n = 0;
  int cn = n;

  while(cn > 0) {
    cn /= 10;
    len_n++;
  }

  int fact = 1;

  for(int i = 0;i < len_n;i++){
    fact = 1LL * fact * 10 % k;
  }

  vector<int> dp(k, -1);
  vector<int> visited(k, 0);
  dp[0] = 0;
  visited[0] = 1;

  printf("%d\n", calc(dp, visited, n % k, fact, n % k));

  return 0;
}
