#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

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

int n,k,b;
vector<int> p;

int main(){

  scanf("%d %d %d",&n,&k,&b);
  
  p = vector<int>(n + 1,0);

  p[1] = 1;

  for(int h = 1;h <= k;h++){
    vector<int> next_p = vector<int>(n + 1,0);
    int sum = 0;
    int coef = 1;
    for(int i = 1;i <= n;i++){
      next_p[1] = add(next_p[1],mult(p[i],coef));
      sum = add(sum,p[i]);
      coef--;
      if(coef == 0){
        coef = n;
      }
    }
    for(int i = 2;i <= n;i++){
      next_p[i] = scad(add(next_p[i - 1],sum),mult(n,p[i]));
    }
    p.swap(next_p);
  }
  
  int ans = 0;

  int coef = 1;
  int where = 1;
  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= n;j++){
      int elem = p[where];
      ans = add(ans,mult(elem,coef));
      coef = mult(coef,b);
      where++;
      if(where > n){
        where = 1;
      }
      printf("%d ",elem);
    }
    where--;
    if(where == 0){
      where = n;
    }
    printf("\n");
  }

  printf("%d\n",ans);

  return 0;
}
