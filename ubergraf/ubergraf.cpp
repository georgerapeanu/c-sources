#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300;
const int inf = 1e9;

int n;
int MOD;

int dp[NMAX + 1][NMAX + 1];
int pw2[NMAX + 1];
int inv[NMAX + 5];


int add(int a,int b,int MOD){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }

  return a;
}

int scad(int a,int b,int MOD){
  a -= b;

  if(a < 0){
    a += MOD;
  }

  return a;
}

int mult(int a,int b,int MOD){
  return a * b % MOD;
}

int lgpow(int base,int exp,int MOD){
  int ans = 1;

  while(exp){
   
    if(exp & 1){
      ans = mult(ans,base,MOD);
    }

    base = mult(base,base,MOD);
    exp >>= 1;
  }

  return ans;
}

int main(){
 
  freopen("ubergraf.in","r",stdin);
  freopen("ubergraf.out","w",stdout);

  scanf("%d %d",&n,&MOD);

  for(int i = 1;i <= n;i++){
    inv[i] = lgpow(i,MOD - 2,MOD);
  }

  pw2[0] = 1;

  for(int i = 1;i <= n;i++){
    pw2[i] = add(pw2[i - 1],pw2[i - 1], MOD);
  }

  dp[1][1] = 1;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= i;j++){
      int cntWays = mult(scad(pw2[j],1,MOD),pw2[i - j],MOD);
      int cappedCntWays = inf;
      if(i <= 8){
        cappedCntWays = (((1 << (j)) - 1) << (i - j));
      }
      int coef = 1;
      for(int k = 1;i + k <= n;k++){
        if(cappedCntWays == 0){
          continue;
        }

        coef = mult(coef,cntWays,MOD);
        coef = mult(coef,inv[k],MOD);
        cntWays = scad(cntWays,1,MOD);
        cappedCntWays--;

        dp[i + k][k] = add(dp[i + k][k],mult(dp[i][j],coef,MOD),MOD); 
      }
    }
  }

  int ans = 0;

  for(int i = 1;i <= n;i++){
    ans = add(ans,dp[n][i],MOD);
  }

  printf("%d\n",ans);

  return 0;
}
