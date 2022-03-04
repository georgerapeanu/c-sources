#include <bits/stdc++.h>

using namespace std;

class DSU{
  int n;
  vector<int> father;
  vector<int> weight;
  vector<int> value;
  vector<int> l;
  vector<int> r;

public:

  DSU(int n){
    this->n = n;
    this->father = vector<int>(n + 1, 0);
    this->weight = vector<int>(n + 1, 1);
    this->l = vector<int>(n + 1, 0);
    this->r = vector<int>(n + 1, 0);
    this->value = vector<int>(n + 1, -1);
    for(int i = 0;i <= n;i++){
      l[i] = r[i] = i;
    }
  }

  int find_root(int nod){
    if(father[nod] == 0){
      return nod;
    }
    return father[nod] = find_root(father[nod]);
  }

  bool unite(int x, int y){
    x = find_root(x);
    y = find_root(y);

    if(x == y){
      return false;
    }
    
    if(weight[x] > weight[y]){
      swap(x, y);
    }
    father[x] = y;
    weight[y] += weight[x];
    l[y] = min(l[y], l[x]);
    r[y] = max(r[y], r[x]);
    value[y] = max(value[x], value[y]);
    return true;
  }

  void reset(){
    for(auto &it:father){
      it = 0;
    }
    for(auto &it:weight){
      it = 1;
    }
    for(int i = 0;i <= n;i++){
      l[i] = r[i] = i;
    }
    for(auto &it:value){
      it = -1;
    }
  }

  pair<int,int> get_range(int nod){
    return {l[find_root(nod)], r[find_root(nod)]};
  }

  void set_value(int nod, int value){
    this->value[find_root(nod)] = value;
  }

  int get_value(int nod){
    return value[find_root(nod)];
  }
};

struct my_query_t{
  int l, r;
  int st, dr;
  int id;

  bool operator < (const my_query_t &other)const{
    return (this->st + this->dr) < other.st + other.dr;
  }

  int mid(){
    return (st + dr) / 2;
  }
};

struct real_query_t{
  int pos;
  int idx;
};

int get_single_unknown(DSU &dsu, int l, int r){
  if(l == r){
    if(dsu.get_value(l) == -1){
      return l;
    }
    return -1;
  }

  for(int nod = l;dsu.get_range(nod).second < r && dsu.get_value(nod) == 0 && dsu.get_value(dsu.get_range(nod).second + 1) == 0;){
    dsu.unite(nod, dsu.get_range(nod).second + 1);
  }
  for(int nod = r;dsu.get_range(nod).first > l && dsu.get_value(nod) == 0 && dsu.get_value(dsu.get_range(nod).first - 1) == 0;){
    dsu.unite(nod, dsu.get_range(nod).first - 1);
  }

  if(dsu.get_value(l) == -1){
    if(dsu.get_range(r).first != l + 1 || dsu.get_value(r) != 0){
      return -1;
    }
    return l;
  }
  
  if(dsu.get_value(r) == -1){
    if(dsu.get_range(l).second != r - 1 || dsu.get_value(l) != 0){
      return -1;
    }
    return r;
  }

  if(dsu.get_range(r).first - dsu.get_range(l).second - 1 != 1){
    return -1;
  }
  return dsu.get_range(r).first - 1;
}

int main(){
  
  int n, q;
  scanf("%d %d", &n, &q);

  DSU dsu(n);
  vector<my_query_t> range_queries[2];
  vector<real_query_t> real_queries;
  vector<int> pos_0;
  for(int i = 0;i < q;i++){
    int t;
    scanf("%d", &t);

    if(t == 0){
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      range_queries[x].push_back({l ,r, 0, 0, i});
      if(x == 0){
        pos_0.push_back(i);
      }
    }else{
      int pos;
      scanf("%d", &pos);
      real_queries.push_back({pos, i});
    }
  }

  for(auto &it:range_queries[1]){
    it.st = -1;
    it.dr = range_queries[0].size();
  }

  vector<pair<int,int> > know(n + 1, make_pair(q + 1, 0));

  for(int idx = 0;idx < (int)range_queries[0].size();idx++){
    if(dsu.get_value(range_queries[0][idx].l) == -1){
      for(int j = dsu.get_range(range_queries[0][idx].l).first;j <= dsu.get_range(range_queries[0][idx].l).second;j++){
        know[j] = {pos_0[idx], 0};
      }
    }
    for(int nod = range_queries[0][idx].l;dsu.get_range(nod).second < range_queries[0][idx].r;){
      int nxt = dsu.get_range(nod).second + 1;
      if(dsu.get_value(nxt) == -1){
        for(int j = dsu.get_range(nxt).first;j <= dsu.get_range(nxt).second;j++){
          know[j] = {pos_0[idx], 0};
        }
      }
      dsu.unite(nod, nxt);
    }
    dsu.set_value(range_queries[0][idx].l, 0);
  }

  while(true){
    dsu.reset();
    sort(range_queries[1].begin(), range_queries[1].end());
  
    bool ok = false;

    int idx = 0;
    
    for(auto &query:range_queries[1]){
      if(query.dr - query.st > 1){
        while(idx <= query.mid()){
          for(int nod = range_queries[0][idx].l;dsu.get_range(nod).second < range_queries[0][idx].r;){
            dsu.unite(dsu.get_range(nod).second + 1, nod);
          }
          dsu.set_value(range_queries[0][idx].l, 0);
          idx++;
        }
        ok = true;
        if(get_single_unknown(dsu, query.l, query.r) != -1){
          know[get_single_unknown(dsu, query.l, query.r)] = {max(pos_0[query.mid()], query.id), 1};
          query.dr = query.mid();
        }else{
          query.st = query.mid();
        }
      }
    }
    if(ok == false){
      break;
    }
  }

  for(auto it:real_queries){
    if(it.idx >= know[it.pos].first){
      printf(know[it.pos].second ? "YES\n":"NO\n");
    }else{
      printf("N/A\n");
    }
  }

  return 0;
}
