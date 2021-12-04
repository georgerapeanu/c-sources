#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

//TODO continue after contest with this implementation
class ModularInt{
  int mod;
 
public:
  
  int a;
  
  ModularInt(){
    ;
  }

  ModularInt(int mod){
    this->a = 0;
    this->mod = mod;
  }

  ModularInt(int a,int mod){
    this->a = a;
    this->mod = mod;
  }

  ModularInt operator + (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = this->a + other.a;
    if(ans.a >= mod){
      ans.a -= mod;
    }
    return ans;
  }

  ModularInt operator - (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = this->a - other.a;
    if(ans.a < 0){
      ans.a += mod;
    }

    return ans;
  }

  ModularInt operator * (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = 1LL * this->a * other.a % mod;
    return ans;
  }
};

vector<ModularInt> calculate_poly_at(int l){
  vector<ModularInt> poly(4,ModularInt(1,MOD));
  
  poly[0] = poly[0] * (ModularInt(l,MOD) - ModularInt(1,MOD));
  poly[0] = poly[0] * (ModularInt(l,MOD) - ModularInt(2,MOD));
  poly[0] = poly[0] * (ModularInt(l,MOD) - ModularInt(3,MOD));
  poly[0] = poly[0] * (ModularInt(0,MOD) - ModularInt(1,MOD));

  poly[1] = poly[1] * (ModularInt(l,MOD) - ModularInt(1,MOD));
  poly[1] = poly[1] * (ModularInt(l,MOD) - ModularInt(2,MOD));
  poly[1] = poly[1] + ((ModularInt(2,MOD) * ModularInt(l,MOD) - ModularInt(3,MOD)) * (ModularInt(l,MOD) - ModularInt(3,MOD)));
  
  poly[2] = poly[2] * (ModularInt(3,MOD) * ModularInt(l,MOD) - ModularInt(6,MOD));
  poly[2] = poly[2] * (ModularInt(0,MOD) - ModularInt(1,MOD));

  poly[3] = ModularInt(1,MOD);

  return poly;
}

class SegmentTree{
  
  struct node_t{
    int gr;
    ModularInt sum;
    vector<ModularInt> powerSum;
    vector<ModularInt> lazy;

    node_t(){
      this->gr = 4;
      this->sum = ModularInt(0,MOD);
      this->powerSum = vector<ModularInt>(4,ModularInt(0,MOD));
      this->lazy = vector<ModularInt>(4,ModularInt(0,MOD));
    }

    node_t(int pos){
      this->gr = 4;
      this->sum = ModularInt(0,MOD);
      this->powerSum = vector<ModularInt>(4,ModularInt(0,MOD));
      this->lazy = vector<ModularInt>(4,ModularInt(0,MOD));
      powerSum[0] = ModularInt(1,MOD);
      for(int i = 1;i < gr;i++){
        powerSum[i] = powerSum[i - 1] * ModularInt(pos,MOD);
      }
    }

    node_t operator + (const node_t &other)const{
      node_t ans;
      ans.gr = 4;
      ans.sum = this->sum + other.sum;
      for(int i = 0;i < ans.gr;i++){
        ans.powerSum[i] = this->powerSum[i] + other.powerSum[i];
        ans.lazy[i] = ModularInt(0,MOD);
      }
      return ans;
    }

    void propag(const vector<ModularInt> &lazy){
      for(int i = 0;i < this->gr;i++){
        this->sum = this->sum + this->powerSum[i] * lazy[i];
        this->lazy[i] = this->lazy[i] + lazy[i];
      }
    }
  };
  
  int n;
  vector<node_t> aint;

  void build(int nod,int st,int dr){
    if(st == dr){
      aint[nod] = node_t(st);
      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propag(int nod,int st,int dr){
    if(st == dr){
      return ;
    }
    aint[nod * 2].propag(aint[nod].lazy);
    aint[nod * 2 + 1].propag(aint[nod].lazy);
    for(auto &it:aint[nod].lazy){
      it = ModularInt(0,MOD);
    }
  }
  
  void update(int nod,int st,int dr,int l,int r, const vector<ModularInt> &poly){
    propag(nod,st,dr);
    if(r < st || l > dr){
      return;
    }
    if(l <= st && dr <= r){
      aint[nod].propag(poly);
      return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,poly);
    update(nod * 2 + 1,mid + 1,dr,l,r,poly);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  ModularInt query(int nod,int st,int dr,int l,int r){
    propag(nod,st,dr);

    if(r < st || l > dr){
      return ModularInt(0,MOD);
    }

    if(l <= st && dr <= r){
      return aint[nod].sum;
    }

    ModularInt ans(0,MOD);

    int mid = (st + dr) / 2;
    ans = ans + query(nod * 2,st,mid,l,r);
    ans = ans + query(nod * 2 + 1,mid + 1,dr,l,r);

    return ans;
  }

public:

  SegmentTree(int n){
    this->n = n;
    aint = vector<node_t>(4 * n + 5,node_t());
    build(1,1,n);
    return;
  }

  void update(int l,int r,const vector<ModularInt> &poly){
    update(1,1,n,l,r,poly);
  }

  ModularInt query(int l,int r){
    return query(1,1,n,l,r);
  }
};

int main(){

  int n,q;

  scanf("%d %d",&n,&q);

  SegmentTree aint(n);

  while(q--){
    int t,l,r;
    scanf("%d %d %d",&t,&l,&r);
    if(t > 0){
      vector<ModularInt> poly = calculate_poly_at(l);
      if(t == 2){
        for(auto &it:poly){
          it = ModularInt(0,MOD) - it;
        }
      }
      aint.update(l,r,poly);
    }else{
      printf("%d\n",aint.query(l,r).a);
    }
  }

  return 0;
}
