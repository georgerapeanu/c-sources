#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e3;
const int MOD = 1e9 + 7;

int n,r;
int p[NMAX + 5];

int dp[2][NMAX + 5];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int main(){
    
  scanf("%d %d",&n,&r);
  
  for(int i = 1;i <= n;i++){
    scanf("%d",&p[i]);
  }
  
  reverse(p + 1, p + 1 + n);

  dp[1][0] = p[1];
  p[n + 1] = r + 1;

  for(int i = 1,l = 1;i <= n;i++, l ^= 1){
    for(int j = 0;j <= n;j++){
      dp[l ^ 1][j] = 0;
    }
    for(int j = 0;j <= n;j++){
      if(i <= j){
        dp[l ^ 1][j] = add(dp[l ^ 1][j],dp[l][j]);
        printf("(%d %d)->(%d %d) with %d\n",i,j,i + 1,j,dp[l][j]);
      }
      if(j < n){
        dp[l][j + 1] = add(dp[l][j + 1],mult(dp[l][j],p[j + 2] - p[j + 1]));
        printf("(%d %d)->(%d %d) with %d\n",i,j,i,j + 1,mult(dp[l][j],p[j + 2] - p[j + 1]));
      }
    }
  }

  printf("%d\n",dp[n & 1][n]);

  return 0;
}
