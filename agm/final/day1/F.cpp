#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int inv2 = MOD / 2 + 1;
const int NMAX = 1e5;

void fix(int &a){
  while(a >= MOD){
    a -= MOD;
  }
  while(a < 0){
    a += MOD;
  }
}

int add(int a,int b){
  fix(a);
  fix(b);
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  fix(a);
  fix(b);
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

pair<int,int> v[NMAX + 5];

int n;
int d;

int eval(const pair<int,int> &a,long long last){
  if(last < a.first){
    return 0;
  }
  ///a.first + a.second * (x - 1) <= last
  ///x - 1 <= (last - a.first) / a.second
  long long ans = (last - a.first) / a.second + 1;
  if(ans >= d){
    ans = d;
  }
  return ans;
}

bool check(long long val){
  int cnt = 0;

  for(int i = 1;i <= n;i++){
    cnt += eval(v[i],val);
    if(cnt >= d){
      return true;
    }
  }
  return (cnt >= d);
}

pair<int,int> contrib(const pair<int,int> &a,long long last){
  last--;
  if(last < a.first){
    return {0,0};
  }
  int last_idx = ((last - a.first) / a.second + 1);
  return {last_idx,mult(last_idx,add(mult(mult(a.second,last_idx - 1),inv2),a.first))};
}

int main(){

  scanf("%d %d",&n,&d);

  int ans = 0;

  for(int i = 1;i <= n;i++){
    scanf("%d %d",&v[i].first,&v[i].second);
    ans = add(ans,v[i].first);
    d--;
    v[i].first += v[i].second;
  }

  ///TODO if it doesnt work, double check this
  long long l = -1;
  long long r = 1e18 + 1;

  while(r - l > 1){
    long long mid = (l + r) / 2;
    if(check(mid)){
      r = mid;
    }else{
      l = mid;
    }
  }

  int cnt = 0;
  for(int i = 1;i <= n;i++){
    pair<int,int> tmp = contrib(v[i],r);
    cnt += tmp.first;
    ans = add(ans,tmp.second);
  }


  ans = add(ans,mult(d - cnt,r % MOD));

  printf("%d\n",ans);

  return 0;
}
