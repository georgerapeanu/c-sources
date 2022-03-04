#include <bits/stdc++.h>
#include "weirdtree.h"

using namespace std;

const int NMAX = 300000;
const int QMAX = 300000;
const int VMAX = 1e9;
const int KMAX = 1e9;

class SegmentTree{
public:
  struct node_t{
    int max1;
    int max2;
    int cntMax;
    long long sum;
    int lazy;

    node_t(){
      this->max1 = 0;
      this->max2 = 0;
      this->cntMax = 0;
      this->sum = 0;
      this->lazy = 0;
    }

    node_t(int val){
      this->max1 = val;
      this->max2 = 0;
      this->cntMax = 1;
      this->sum = val;
      this->lazy = 0;
    }

    node_t operator + (const node_t &other)const{
      node_t ans;

      ans.sum = (this->sum + other.sum);
      ans.lazy = 0;
    
      if(this->max1 == other.max1){
        ans.max1 = this->max1;
        ans.cntMax = this->cntMax + other.cntMax;
        ans.max2 = max(this->max2,other.max2);
      }else if(this->max1 > other.max1){
        ans.max1 = this->max1;
        ans.cntMax = this->cntMax;
        ans.max2 = max(this->max2,other.max1);
      }else{
        ans.max1 = other.max1;
        ans.cntMax = other.cntMax;
        ans.max2 = max(this->max1,other.max2);
      }
    
      return ans;
    }

    void propagate(int lazy){
      this->max1 -= lazy;
      this->sum -= 1LL * lazy * this->cntMax;
      this->lazy += lazy;
    }

  };

private:
  int n;
  vector<node_t> aint;

  void build(int nod,int st,int dr,int v[]){
    if(st == dr){
      aint[nod] = node_t(v[st]);
      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid,v);
    build(nod * 2 + 1,mid + 1,dr,v);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propagate(int nod,int st,int dr){
    if(aint[nod].lazy == 0 || st == dr){
      return ;
    }
    int tmpMax = max(aint[nod * 2].max1,aint[nod * 2 + 1].max1);
    if(aint[nod * 2].max1 == tmpMax){
      aint[nod * 2].propagate(aint[nod].lazy);
    }
    if(aint[nod * 2 + 1].max1 == tmpMax){
      aint[nod * 2 + 1].propagate(aint[nod].lazy);
    }

    aint[nod].lazy = 0;
  }
  

  void updateSet(int nod,int st,int dr,int pos,int value){
    propagate(nod,st,dr);

    if(dr < pos || st > pos){
      return ;
    }
    if(st == dr){
      aint[nod] = node_t(value);
      return ;
    }

    int mid = (st + dr) / 2;

    updateSet(nod * 2,st,mid,pos,value);
    updateSet(nod * 2 + 1,mid + 1,dr,pos,value);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void updateSubtract(int nod,int st,int dr,int l,int r,int value,int &bonus,int maxValue){
    propagate(nod,st,dr);
    if(value + (bonus > 0) == 0 || dr < l || st > r || (l <= st && dr <= r && aint[nod].max1 != maxValue)){
      return ;
    }
    if(l <= st && dr <= r && (bonus == 0 || bonus >= dr - st + 1) && (aint[nod].max2 == 0 || aint[nod].max1 - value - (bonus > 0) > aint[nod].max2)){
      aint[nod].propagate(value + (bonus > 0));
      bonus -= (bonus > 0) * aint[nod].cntMax;
      return ;
    }
    int mid = (st + dr) / 2;
 
    updateSubtract(nod * 2,st,mid,l,r,value,bonus,maxValue);
    updateSubtract(nod * 2 + 1,mid + 1,dr,l,r,value,bonus,maxValue);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  node_t query(int nod,int st,int dr,int l,int r){
    propagate(nod,st,dr);
    if(dr < l || st > r){
      return node_t();
    }

    if(l <= st && dr <= r){
      return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
  }
  

public:

  SegmentTree(){
    ;
  }

  SegmentTree(int n,int v[]){
    this->n = n;
    this->aint = vector<node_t>(4 * n + 5, node_t());
    build(1,1,n,v);
  }
  
  node_t query(int st,int dr){
    return this->query(1,1,n,st,dr);
  }

  void updateSet(int pos,int value){
    this->updateSet(1,1,n,pos,value);
  }

  void updateSubtract(int l,int r,int k,int bonus,int maxValue){
    this->updateSubtract(1,1,n,l,r,k,bonus,maxValue);
  }
};

int global_n;
SegmentTree aint;

void initialise(int n,int q,int v[]){
  assert(1 <= n && n <= NMAX);
  assert(1 <= q && q <= QMAX);
  global_n = n;
  for(int i = 1;i <= n;i++){
    assert(1 <= v[i] && v[i] <= VMAX);
  }
  aint = SegmentTree(n, v);
}

void cut(int l,int r,int k){
  assert(1 <= l && l <= r && r <= global_n && 1 <= k && k <= KMAX);
  while(k > 0){
    SegmentTree::node_t tmp = aint.query(l,r);
    if(tmp.max1 == 0){
      break;
    }
    if((tmp.max1 - tmp.max2) <= k / tmp.cntMax){
      k -= (tmp.max1 - tmp.max2) * tmp.cntMax;
      aint.updateSubtract(l,r,tmp.max1 - tmp.max2,0,tmp.max1);
    }else{
      int divResult = k / tmp.cntMax;
      aint.updateSubtract(l,r,divResult,k - divResult * tmp.cntMax,tmp.max1);
      k = 0;
    }
  }
}

void magic(int i,int x){
  assert(1 <= i && i <= global_n && 1 <= x && x <= VMAX);
  aint.updateSet(i,x);
}

long long inspect(int l,int r){
  assert(1 <= l && l <= r && r <= global_n);
  return aint.query(l,r).sum;
}

