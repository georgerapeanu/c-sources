#include <bits/stdc++.h>

using namespace std;

const int DECK_SIZE = 52;

struct node_t{
  int n;
  vector<int> sum;
  vector<int> lazy;
  node_t(){
    sum = vector<int>(DECK_SIZE, 0);
    lazy = vector<int>(DECK_SIZE, 0);
    for(int i = 0;i < DECK_SIZE;i++){
      lazy[i] = i;
    }
  }

  void propagate(const vector<int> &lazy){
    node_t tmp;
    for(int i = 0;i < (int)lazy.size();i++){
      tmp.sum[i] = sum[lazy[i]];
      tmp.lazy[i] = this->lazy[lazy[i]];
    }
    this->sum = tmp.sum;
    this->lazy = tmp.lazy;
  }

  node_t operator + (const node_t &other)const{
    node_t ans;
    for(int i = 0;i < (int)sum.size();i++){
      ans.sum[i] = this->sum[i] + other.sum[i]; 
    }
    return ans;
  }

  void initialize_with_cards(){
    for(int i = 0;i < DECK_SIZE;i++){
      sum[i] = (i % 13) + 1;
      lazy[i] = i;
    }
  }

  void reset_lazy(){
    for(int i = 0;i < (int)lazy.size();i++){
      lazy[i] = i;
    }
  }
};

class SegmentTree{
  int n;
  vector<node_t> aint;

  void build(int nod, int st, int dr){
    if(st == dr){
      this->aint[nod].initialize_with_cards();
      return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2, st, mid);
    build(nod * 2 + 1, mid + 1, dr);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propagate(int nod, int st, int dr){
    if(st == dr){
      return ;
    }
    aint[nod * 2].propagate(aint[nod].lazy);
    aint[nod * 2 + 1].propagate(aint[nod].lazy);
    aint[nod].reset_lazy();
  }

  void update(int nod, int st, int dr, int l, int r, int i, int j){
    propagate(nod,st,dr);
    if(dr < l || r < st){
      return ; 
    }
    if(l <= st && dr <= r){
      swap(aint[nod].sum[i], aint[nod].sum[j]);
      swap(aint[nod].lazy[i], aint[nod].lazy[j]);
      return; 
    }

    int mid = (st + dr) / 2;

    update(nod * 2, st, mid, l, r, i, j);
    update(nod * 2 + 1, mid + 1, dr, l, r, i, j);
    
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }
  
  node_t query(int nod, int st, int dr, int l, int r){
    propagate(nod,st,dr);
    if(dr < l || r < st){
      return node_t(); 
    }
    if(l <= st && dr <= r){
      return aint[nod]; 
    }

    int mid = (st + dr) / 2;

    return query(nod * 2, st, mid, l, r) + query(nod * 2 + 1, mid + 1, dr, l, r);
  }

public:
   
  SegmentTree(int n){
    this->n = n;
    this->aint = vector<node_t>(4 * n + 5);
    this->build(1,0,n - 1);
  }
  
  void update(int a, int b, int i, int j){
    this->update(1, 0, n - 1, a, b, i, j);
  }

  int query(int a, int b){
    return this->query(1, 0, n - 1, a, b).sum[DECK_SIZE - 1];
  }
};

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n, q;
    scanf("%d %d", &n, &q); 

    SegmentTree aint(n);

    while(q--){
      int t;
      scanf("%d", &t);

      if(t == 0) {
        int a, b, x, y;
        scanf("%d %d %d %d", &a, &b, &x, &y);
        aint.update(a, b, x, y); 
      } else {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", aint.query(a, b));
      }
    }
  }



  return 0;
}
