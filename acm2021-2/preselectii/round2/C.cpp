#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

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

int lgpow(int b,int e){
  int p = 1;

  while(e){
    if(e & 1){
      p = mult(p,b);
    }
    e >>= 1;
    b = mult(b,b);
  }
  return p;
}

int x,y;


int main(){

  scanf("%d %d",&x,&y);
  if(y % x != 0){
    printf("%d\n",0);
    return 0;
  }

  vector<int> divs;

  for(int i = 1;1LL * i * i <= y;i++){
    if(y % i == 0){
      divs.push_back(i);
      if(1LL * i * i != y){
        divs.push_back(y / i);
      }
    }
  }

  sort(divs.begin(),divs.end());
  vector<int> f(divs.size());

  for(int i = (int)divs.size() - 1;i >= 0;i--){
    f[i] = lgpow(2,y / divs[i] - 1);
    for(int j = i + 1;j < (int)divs.size();j++){
      if(divs[j] % divs[i] == 0){
        f[i] = scad(f[i],f[j]);
      }
    }
    if(divs[i] == x){
      printf("%d\n",f[i]);
      return 0;
    }
  }



  return 0;
}
