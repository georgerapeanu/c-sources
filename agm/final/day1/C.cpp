#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int MOD = 998244353;
const int inv2 = MOD / 2 + 1;

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

int pw2[NMAX + 5];

int n;
pair<int,int> point[NMAX + 5];
pair<int,int> tmp[NMAX + 5];

pair<int,int> pvt;

long long det(const pair<int,int> &a,const pair<int,int> &b,const pair<int,int> &c){
  return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

bool cmp(const pair<int,int> &a,const pair<int,int> &b){
  return det(pvt,a,b) > 0;
}

int dist(const pair<int,int> &a,const pair<int,int> &b){
  return add(mult(a.first - b.first,a.first - b.first),mult(a.second - b.second,a.second - b.second));
}

int main(){

  pw2[0] = 1;

  for(int i = 1;i <= NMAX;i++){
    pw2[i] = add(pw2[i - 1],pw2[i - 1]);
  }

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d %d",&point[i].first,&point[i].second);
  }

  int ans = 0;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= n;j++){
      tmp[j] = point[j];
    }
    swap(tmp[1],tmp[i]);
    pvt = tmp[1];
    sort(tmp + 2,tmp + 1 + n,cmp);

    for(int j = 2;j <= n;j++){
      ans = add(ans,mult(scad(add(pw2[j - 2],pw2[n - j]),2),dist(pvt,tmp[j])));
      printf("(%d %d) (%d %d) with %d\n",pvt.first,pvt.second,tmp[j].first,tmp[j].second,dist(pvt,tmp[j]));
      printf("has weight %d\n",scad(add(pw2[j - 2],pw2[n - j]),2));
    }
  } 

  ans = mult(ans,inv2);

  printf("%d\n",ans);


  return 0;
}
