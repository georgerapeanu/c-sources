#include <bits/stdc++.h>

using namespace std;

const int VMAX = 100;

int phi[VMAX + 5];
int p[VMAX + 1][VMAX][2 * VMAX + 5];

void fix(int &val,const int &mod){
  while(val >= mod){
    val -= mod;
  }
  while(val < 0){
    val += mod;
  }
}

class FenwickTree{
  int n;
  int mod;
  vector<int> aib;

  public:

  FenwickTree(){
    ;
  }
   
  FenwickTree(int n,int mod){
    this->n = n;
    this->mod = mod;
    this->aib = vector<int>(n + 1,0);
  }

  void update(int pos,int val){
    fix(val,mod);
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] += val;
      fix(aib[pos],mod);
    }
  }

  int query(int pos){
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
      ans += aib[pos];
      fix(ans,mod);
    }
    return ans;
  }
};

class FenwickTree2{
  int n;
  int mod;
  FenwickTree a;
  FenwickTree b;

public:

  FenwickTree2(){
  }

  FenwickTree2(int n,int mod){
    this->n = n;
    this->mod = mod;
    a = FenwickTree(n,mod);
    b = FenwickTree(n,mod);
  }

  void update(int l,int r,int val){
    fix(val,mod);
    a.update(l,val);
    b.update(l,-val * (l - 1) % mod);
    a.update(r + 1,-val);
    b.update(r + 1,val * (r) % mod);
  }

  int eval(int pos){
    return (a.query(pos) * pos + b.query(pos)) % mod;
  }

  int query(int l,int r){
    int ans = eval(r) - eval(l - 1);
    fix(ans,mod);
    return ans;
  }
};

int n,q;
FenwickTree2 stuff[VMAX + 1];

int get_pow(int x,int y,int mod){
  x %= mod;
  if(y <= 2 * phi[mod]){
    return p[mod][x][y];
  }
  int tmp = y % phi[mod];
  y = phi[mod] + tmp;
  if(tmp == 0){
    y += phi[mod];
  }
  return p[mod][x][y];
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }

  return ans;
}

int main(){
  
  for(int i = 1 ;i <= VMAX;i++){
    phi[i] += i;
    for(int j = i + i;j <= VMAX;j += i){
      phi[j] -= phi[i];
    }
  }

  for(int mod = 1;mod <= VMAX;mod++){
    for(int j = 0;j < mod;j++){
      p[mod][j][0] = 1;
      p[mod][j][1] = j;
      for(int k = 2;k <= 2 * phi[mod];k++){
        p[mod][j][k] = p[mod][j][k - 1] * j % mod;
      }
    }
  }

  n = i32();
  q = i32();

  for(int mod = 1;mod <= VMAX;mod++){
    stuff[mod] = FenwickTree2(n,mod);
  }

  while(q--){
    int t,l,r;
    t = i32();
    l = i32();
    r = i32();
    if(t == 0){
      int x,y;
      x = i32();
      y = i32();
      for(int i = 1;i <= VMAX;i++){
        stuff[i].update(l,r,get_pow(x,y,i));
      }
    }else{
      int m;
      m = i32();
      printf("%d\n",stuff[m].query(l,r));
    }
  }

  return 0;
}
