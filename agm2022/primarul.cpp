#include <bits/stdc++.h>

using namespace std;


class ModInt{
  static const int MOD = 998244353;

  int value;

public:

  ModInt(){
    this->value = 0;
  }

  ModInt(int value){
    this->value = value;
  }

  ModInt operator + (const ModInt other) const {
    ModInt answer(this->value + other.value);
    if(answer.value >= MOD){
      answer.value -= MOD;
    }
    return answer;
  }

  ModInt operator - (const ModInt other) const {
    ModInt answer(this->value - other.value);
    if(answer.value < 0){
      answer.value += MOD;
    }
    return answer;
  }

  ModInt operator * (const ModInt other) const {
    return ModInt(1LL * this->value * other.value % MOD);
  }

  ModInt operator / (const ModInt other) const{
    int e = MOD - 2;
    ModInt b(other.value);
    ModInt p(1);

    while(e){
      if(e & 1){
        p = p * b;
      }
      b = b * b;
      e >>= 1;
    }

    return *this * p;
  }

  explicit operator int() const {
    return this->value;
  }

  ModInt& operator = (const int value){
    this->value = value;
    return *this;
  }

  bool operator == (const ModInt &other) const{
    return this->value == other.value;
  }

  bool operator != (const ModInt &other) const{
    return this->value != other.value;
  }
};

//1 - indexed
class SegmentTree{
private:
  
  struct node_t{
    pair<ModInt, ModInt> lazy;
    ModInt value;
    int st;
    int dr;

    node_t(ModInt value, int st, int dr){
      this->value = value;
      this->st = st;
      this->dr = dr;
      this->lazy = {1, 0};
    }
    
    node_t operator + (const node_t &other) const {
      node_t answer(0, 0, 0);
      answer.st = min(this->st, other.st);
      answer.dr = max(this->dr, other.dr);
      answer.value = this->value + other.value;
      answer.lazy = {1, 0};
      return answer;
    }

    void propagate(const pair<ModInt, ModInt> &lazy){
       this->value = lazy.first * this->value + lazy.second * (dr - st + 1);

       ///c(ax+b)+d = acx + bc + d
       this->lazy.first = lazy.first * this->lazy.first;
       this->lazy.second = lazy.second + lazy.first * this->lazy.second;
    }
  };

  int n;
  vector<node_t> aint;

  void build(int nod, int st, int dr, const vector<ModInt> &v) {
    if(st == dr){
      this->aint[nod] = node_t(v[st], st , dr);

      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2, st, mid, v);
    build(nod * 2 + 1, mid + 1, dr, v);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propagate(int nod){
    if(aint[nod].lazy == make_pair(ModInt(1), ModInt(0)) || aint[nod].st == aint[nod].dr){
      return ;
    }
    aint[nod * 2].propagate(aint[nod].lazy);
    aint[nod * 2 + 1].propagate(aint[nod].lazy);
    aint[nod].lazy = make_pair(1, 0);
  }

  void updateRange(int nod, int st, int dr, int l, int r, const pair<ModInt, ModInt> &lazy){
    propagate(nod);
    if(r < st || l > dr){
      return ;
    }

    if(l <= st && dr <= r){
      aint[nod].propagate(lazy);
      return ;
    }

    int mid = (st + dr) / 2;

    updateRange(nod * 2, st, mid, l, r, lazy);
    updateRange(nod * 2 + 1, mid + 1, dr, l, r, lazy);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  node_t queryRange(int nod, int st, int dr, int l, int r){
    propagate(nod);
    if(r < st || l > dr){
      return node_t(0, +n, -n);
    }
    
    if(l <= st && dr <= r){
      return aint[nod];
    }

    int mid = (st + dr) / 2;

    return queryRange(nod * 2, st, mid, l, r) + queryRange(nod * 2 + 1, mid + 1, dr, l , r);
  }

public:
  

  // values should be 1 indexed
  SegmentTree(const vector<ModInt> &values){
    this->n = (int)values.size() - 1;
    this->aint = vector<node_t>(4 * n + 5, node_t(0, 0, 0));
    this->build(1, 1, n, values);
  }

  void updateRange(int l, int r, const pair<ModInt, ModInt> &lazy){
    this->updateRange(1, 1, n, l, r, lazy);
  }

  ModInt queryRange(int l, int r){
    return this->queryRange(1, 1, n, l, r).value;
  }
};

int n;
vector<vector<int> > graph;
vector<int> heavy_son;
vector<int> heavy_root;
vector<int> lft;
vector<int> rgt;
vector<int> weight;
vector<int> father;
int last_index;

void predfs(int nod, int tata){
  weight[nod] = 1;
  father[nod] = tata;
  for(auto it:graph[nod]){
     if(it == tata){
      continue;
     }
     predfs(it, nod);
     weight[nod] += weight[it];
  }
}

void dfs(int nod, int tata){
  heavy_son[nod] = -1;
  if(tata == 0 || heavy_son[tata] != nod){
    heavy_root[nod] = nod;
  }else{
    heavy_root[nod] = heavy_root[tata];
  }
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    if(heavy_son[nod] == -1 || weight[it] > weight[heavy_son[nod]]){
      heavy_son[nod] = it;
    }
  }
  for(auto &it:graph[nod]){
    if(it == heavy_son[nod]){
      swap(it, graph[nod][0]);
      break;
    }
  }
  lft[nod] = ++last_index;
 
 for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it, nod);
  }
  rgt[nod] = last_index;
}

void apply(int u, int v, const pair<ModInt, ModInt> &value, SegmentTree& aint){
  while(heavy_root[u] != heavy_root[v]){
    if(weight[heavy_root[u]] > weight[heavy_root[v]]){
      swap(u, v);
    }
    aint.updateRange(lft[heavy_root[u]], lft[u], value);
    u = father[heavy_root[u]];
  }
  
  if(weight[u] > weight[v]){
    swap(u, v);
  }

  aint.updateRange(lft[v], lft[u], value);
}

int main(){
  
  scanf("%d", &n);
  graph = vector<vector<int> > (n + 1, vector<int>());;
  heavy_son = vector<int>(n + 1, 0);
  lft = vector<int>(n + 1, 0);
  rgt = vector<int>(n + 1, 0);
  weight = vector<int>(n + 1, 0);
  father = vector<int>(n + 1, 0);
  heavy_root = vector<int>(n + 1, 0);

  vector<int> initial(n + 1, 0);

  for(int i = 1;i <= n;i++){
//    scanf("%d", &initial[i]);
    initial[i] = 1;
  }

  for(int i = 1;i < n;i++){
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  predfs(1, 0);
  dfs(1, 0);

  vector<ModInt> values(n + 1, 0);

  for(int i = 1;i <= n;i++){
    values[lft[i]] = initial[i];
  }

  SegmentTree aint(values);
  
  int q;

  scanf("%d", &q);

  while(q--){
    int t;
    scanf("%d", &t);

    if(t == 1){ //x -> (1 - p) * x
      int u, v, p, q;
      scanf("%d %d %d %d", &u, &v, &p, &q);
      ModInt prob = ModInt(p) / q;
      apply(u, v, {ModInt(1) - prob, ModInt(0)}, aint);
    }else if(t == 2){ // x -> 1 - (1 - x) * (1 - p) = 1 - (1 - x - p + px) = x + p - px = x(1-p) + p
      int u, v, p, q;
      scanf("%d %d %d %d", &u, &v, &p, &q);
      ModInt prob = ModInt(p) / q;
      apply(u, v, {ModInt(1) - prob, prob}, aint);
    
    }else{
      int nod;
      scanf("%d", &nod);
      printf("%d\n", (int)aint.queryRange(lft[nod], rgt[nod]));
    }
  }

  return 0;
}

