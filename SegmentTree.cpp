#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

struct lazy_t{
  void propagate(const lazy_t &lazy, int st, int dr){
    // LAZY TO LAZY PROPAGATION HERE
  }

  lazy_t(){
    // DEFAULT lazy_t CONSTRUCTOR
  }
};

struct node_t{
  bool has_lazy;
  lazy_t lazy;
  int a;
  int b;

  node_t(){
    has_lazy = false;
    lazy = lazy_t();
    a = 0;
    b = 0;
  }

  node_t(int a, int b){
    this->has_lazy = false;
    this->a = a;
    this->b = b;
    this->lazy = lazy_t();
  }

  node_t operator + (const node_t &other) {
    node_t answer;
    answer.has_lazy = false;
    answer.lazy = lazy_t();
    // NODE COMPOSITON LAW HERE
    answer.a = (1LL * other.a * this->a) % MOD;
    answer.b = (1LL * other.a * this->b + other.b) % MOD; 
    return answer;
  }
  
  void propagate(const lazy_t &other, int st, int dr) { 
    this->has_lazy = true;
    this->lazy.propagate(other, st, dr); 
    //LAZY TO NODE PROPAGATION HERE
  }
};

// 0-indexed segment tree, all intervals are [l, r)
class SegmentTree{
  int n;
  vector<node_t> aint;

  void propagate(int nod, int st, int dr) {
    //checks for leaves are done with st+1 >= dr, be careful if it might be problematic
    if(st + 1 >= dr || !aint[nod].has_lazy){
      return ;
    }
    int mid = (st + dr) / 2;
    aint[nod * 2].propagate(aint[nod].lazy, st, mid);
    aint[nod * 2 + 1].propagate(aint[nod].lazy, mid, dr);
    aint[nod].lazy = lazy_t();
    aint[nod].has_lazy = false;
  }

  void updateSet(int nod, int st, int dr, int pos, int a, int b){
    propagate(nod, st, dr);
    if(st + 1 >= dr){
      aint[nod] = node_t(a, b); 
      return ;
    }
    int mid = (st + dr) / 2;
    if(pos < mid){
      updateSet(nod * 2, st, mid, pos, a, b);
    } else {
      updateSet(nod * 2 + 1, mid, dr, pos, a, b);  
    }
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void updateRange(int nod, int st, int dr, int l, int r, const lazy_t &lazy) {
    propagate(nod, st, dr);
    
    if(l <= st && dr <= r){
      aint[nod].propagate(lazy, st, dr);
      return ;
    }

    int mid = (st + dr) / 2;

    if(l < mid){
      updateRange(nod * 2, st, mid, l, r, lazy); 
    }
    
    if(mid < r){
      updateRange(nod * 2 + 1, mid, dr, l, r, lazy); 
    }

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  node_t query(int nod, int st, int dr, int l, int r){
    //cerr << st << " " << dr << " " << l << " " << r << "\n";
    propagate(nod, st, dr);

    if(l <= st && dr <= r){
       return aint[nod];
    }

    int mid = (st + dr) / 2;

    if(r <= mid){
      return query(nod * 2, st, mid, l, r);
    } else if(mid <= l){
      return query(nod * 2 + 1, mid, dr, l, r);
    } else {
      return query(nod * 2, st, mid, l, r) + query(nod * 2 + 1, mid, dr, l, r);
    }
  }

  void build(int nod, int st, int dr, const vector<pair<int, int>> &v){
    if(st + 1>= dr){
      this->aint[nod] = node_t(v[st].first, v[st].second);
      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2, st, mid, v);
    build(nod * 2 + 1, mid, dr, v);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

public:

  SegmentTree(const vector<pair<int, int> > &v){
    this->n = (int)v.size();
    this->aint = vector<node_t>(4 * this->n + 5);
    this->build(1, 0, n, v); 
  }

  void updateSet(int pos, int a, int b){
    this->updateSet(1, 0, n, pos, a, b); 
  }

  void updateRange(int l, int r){
    this->updateRange(1, 0, n, l, r, lazy_t());
  }

  pair<int, int> query(int l, int r){
    node_t answer = this->query(1, 0, n, l, r);
    return {answer.a, answer.b};
  }
};

int main(){
  int n, q;
  scanf("%d %d", &n, &q);
  vector<pair<int, int>> v(n);

  for(int i = 0;i < n;i++){
    scanf("%d %d", &v[i].first, &v[i].second);
  }

  SegmentTree aint(v);

  while(q--){
    int t;
    scanf("%d", &t);
    
    if(t == 0){
      int p, a, b;
      scanf("%d %d %d", &p, &a, &b);
      aint.updateSet(p, a, b);
    }else {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      pair<int, int> line = aint.query(l, r);
      printf("%d\n", (1LL * line.first * x + line.second) % MOD);
    }
  }

  return 0;
}
