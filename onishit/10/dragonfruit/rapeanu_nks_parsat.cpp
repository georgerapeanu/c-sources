#include <bits/stdc++.h>

using namespace std;

///dp[i][j][k][0/1] -> numarul minim de cactusi daca din primii i cactusi avem suma j, folosind k intervale, din care ultimu e inchis/deschis
///cnt_dp[i][j][k][0/1] -> numarul de solutii daca din primii i cactusi avem suma j, folosind k intervale, din care ultimu e inchis/deschis

FILE *f = fopen("dragonfruit.in", "r");
FILE *g = fopen("dragonfruit.out", "w");

const int TMAX = 5;
const int VMAX = 1000;
const int NMAX = 1e5;
const int KMAX = 1000;
const int SMAX = 15;
const int inf = 1e9;
const int MOD = 1e9 + 7;

int dp[2][KMAX + 1][SMAX + 1][2];
int cnt_dp[2][KMAX + 1][SMAX + 1][2];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;
int i32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, f);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, f);
    }
  }
  return ans;
}

int main(){

  int t;

  t = i32();
  assert(t <= TMAX);

  while(t--){
    int n, k, s;    
    n = i32();
    k = i32();
    s = i32();
    assert(n <= NMAX);
    assert(k <= KMAX);
    assert(s <= SMAX);

    for(int i = 0;i <= k;i++){
      for(int j = 0;j <= s;j++){
        dp[0][i][j][0] = dp[0][i][j][1] = inf;
        cnt_dp[0][i][j][0] = cnt_dp[0][i][j][1] = 0;
      }
    }

    dp[0][0][0][0] = 0;
    cnt_dp[0][0][0][0] = 1;

    for(int i = 1;i <= n;i++){
      int value;
      value = i32();
      assert(value <= VMAX);

      for(int j = 0;j <= k;j++){
        for(int l = 0;l <= s;l++){
          cnt_dp[i & 1][j][l][1] = 0;
          dp[i & 1][j][l][1] = inf;

          if(j >= value){
            if(l <= 0 || dp[1 - (i & 1)][j - value][l][1] + 1 <= dp[1 - (i & 1)][j - value][l - 1][0] + 1){
              dp[i & 1][j][l][1] = dp[1 - (i & 1)][j - value][l][1] + 1;
              cnt_dp[i & 1][j][l][1] = add(cnt_dp[i & 1][j][l][1], cnt_dp[1 - (i & 1)][j - value][l][1]);
            }
            if(l > 0 && dp[1 - (i & 1)][j - value][l][1] + 1 >= dp[1 - (i & 1)][j - value][l - 1][0] + 1){
              dp[i & 1][j][l][1] = dp[1 - (i & 1)][j - value][l - 1][0] + 1;
              cnt_dp[i & 1][j][l][1] = add(cnt_dp[i & 1][j][l][1], cnt_dp[1 - (i & 1)][j - value][l - 1][0]);
            
            }
          }
        }
      }
      for(int j = 0;j <= k;j++){
        for(int l = 0;l <= s;l++){
          cnt_dp[i & 1][j][l][0] = 0;
          dp[i & 1][j][l][0] = inf;
          
          if(dp[1 - (i & 1)][j][l][0] <= dp[(i & 1)][j][l][1]){
            dp[i & 1][j][l][0] = dp[1 - (i & 1)][j][l][0];   
            cnt_dp[i & 1][j][l][0] = add(cnt_dp[i & 1][j][l][0], cnt_dp[1 - (i & 1)][j][l][0]);
          }
          
          if(dp[1 - (i & 1)][j][l][0] >= dp[(i & 1)][j][l][1]){
            dp[i & 1][j][l][0] = dp[(i & 1)][j][l][1];   
            cnt_dp[i & 1][j][l][0] = add(cnt_dp[i & 1][j][l][0], cnt_dp[(i & 1)][j][l][1]);
          }
        }
      }
    }
    pair<int, int> ans = {inf, 0};
    for(int i = 0;i <= s;i++){
      if(ans.first > dp[n & 1][k][i][0]){
        ans.first = dp[n & 1][k][i][0];
        ans.second = 0;
      }
      if(ans.first >= dp[n & 1][k][i][0]){
        ans.second = add(ans.second, cnt_dp[n & 1][k][i][0]);
      }
    }
    
    if(ans.first == inf){
      ans.first = 0;
    }
    fprintf(g, "%d %d\n", ans.first, ans.second);
  }
  

  fclose(f);
  fclose(g);

  return 0;
}
