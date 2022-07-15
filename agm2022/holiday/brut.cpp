#include <bits/stdc++.h>

using namespace std;

class DSU{
  int n;
  vector<int> father;
  vector<int> weight;

public:
  
  DSU(int n){
    this->n = n;
    this->father = vector<int>(n + 1, 0);
    this->weight = vector<int>(n + 1, 1);
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

    weight[y] += weight[x];
    father[x] = y;

    return true;
  }

  int get_weight(int nod)const{
    return weight[nod];
  }

  void reset(){
    for(auto &it:father){
      it = 0;
    }
    
    for(auto &it:weight){
      it = 1;
    }
  }
};

struct query_t{
  int x, y;
  int count;
  int lca;
  int st, dr;
  int id;

  query_t(){
    ;
  }

  query_t(int x, int y, int count, int lca, int st, int dr, int id){
    this->x = x;
    this->y = y;
    this->count = count;
    this->lca = lca;
    this->st = st;
    this->dr = dr;
    this->id = id;
  }

  int mid()const{
    return (st + dr) / 2;
  }

  bool operator < (const query_t &other) const{
    if(this->mid() != other.mid()){
      return this->mid() < other.mid();
    }
    return this->id < other.id;
  }
};

void dfs(int nod,int tata, const vector<vector<int> > &graph, vector<vector<int> > &father, vector<int> &lvl){
  father[0][nod] = tata;
  lvl[nod] = 1 + lvl[tata];
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it, nod, graph, father, lvl);
  }
}

int lca(int x, int y, const vector<vector<int> > &father, const vector<int> &lvl){
  if(lvl[x] > lvl[y]){
    swap(x, y);
  }

  for(int h = (int)father.size() - 1;h >= 0;h--){
    if((lvl[y] - lvl[x]) >= (1 << h)){
      y = father[h][y];
    }
  }

  if(x == y){
    return x;
  }
  
  for(int h = (int)father.size() - 1;h >= 0;h--){
    if(father[h][x] != father[h][y]){
      x = father[h][x];
      y = father[h][y];
    }
  }

  return father[0][x];
}

int get_reachable_on_path(const query_t &query, const vector<vector<int> > &father, const vector<int> &lvl, DSU &dsu){
  if(dsu.find_root(query.x) == dsu.find_root(query.y)){
    return lvl[query.x] + lvl[query.y] - 2 * lvl[query.lca] + 1;
  }
  if(dsu.find_root(query.x) == dsu.find_root(query.lca)){
    int nod = query.y;
    for(int h = (int)father.size() - 1;h >= 0;h--){
      if(lvl[father[h][nod]] >= lvl[query.lca]){
        if(dsu.find_root(father[h][nod]) != dsu.find_root(query.x)){
          nod = father[h][nod];
        }
      }
    }
    return lvl[query.x] - lvl[query.lca] + lvl[nod] - lvl[query.lca];
  }else{
    int nod = query.x;
    for(int h = (int)father.size() - 1;h >= 0;h--){
      if(lvl[father[h][nod]] >= lvl[query.lca]){
        if(dsu.find_root(father[h][nod]) == dsu.find_root(query.x)){
          nod = father[h][nod];
        }
      }
    }
    return lvl[query.x] - lvl[nod] + 1;
  }
}

int get_reachable_on_path_brute(const query_t &query, const vector<vector<int> > &graph, map<pair<int, int> , int> &edges){
  queue<int> nodes;
  vector<bool> viz(graph.size(), false);
  vector<bool> viz2(graph.size(), false);
  vector<int> ant(graph.size(), 0);
  nodes.push(query.x);
  viz[query.x] = 1;
  viz2[query.x] = 1;
  ant[query.x] = 0;
  while(nodes.empty() == false){
    int node = nodes.front();
    nodes.pop();
    for(auto it:graph[node]){
      if(viz[it] == false){
        viz[it] = true;
        ant[it] = node;
        nodes.push(it);
        if(viz2[it] == false && query.mid() >= edges[{node, it}]){
          viz2[it] = viz2[node];
        }
      }
    }
  }
  int node = query.y;
  while(viz2[node] == false){
    node = ant[node];
  }
  int ans = 1;
  while(ant[node] != 0){
    ans++;
    node = ant[node];
  }
  return ans;
}

int get_reachable(const query_t &query, const vector<vector<int> > &graph, map<pair<int, int> , int> &edges){
  queue<int> nodes;
  vector<bool> viz(graph.size(), false);
  nodes.push(query.x);
  viz[query.x] = 1;
  int ans = 0;
  while(nodes.empty() == false){
    int node = nodes.front();
    nodes.pop();
    ans++;
    for(auto it:graph[node]){
      if(viz[it] == false && edges[{node, it}] <= query.mid()){
        viz[it] = true;
        nodes.push(it);
      }
    }
  }
  return ans;
}

bool ok(const query_t &query, const vector<vector<int> > &father, const vector<int> &lvl, DSU &dsu, const vector<vector<int> > &graph, map<pair<int, int> , int> &edges){
  
 // printf("query is %d %d %d %d %d %d %d\n", query.id, query.st, query.dr, query.x, query.y, query.lca, query.count);
 // printf("reachable %d\n", dsu.get_weight(dsu.find_root(query.x)));
 // printf("on path %d\n", get_reachable_on_path(query, father, lvl, dsu));
  
 // printf("debug %d %d %d %d lca is %d\n", query.x, query.y, lvl[query.x], lvl[query.y], query.lca);
 // printf("%d %d\n", get_reachable_on_path(query, father, lvl, dsu), get_reachable_on_path_brute(query, graph, edges));
 // printf("%d %d\n", dsu.get_weight(dsu.find_root(query.x)), get_reachable(query, graph, edges));
 // assert(dsu.get_weight(dsu.find_root(query.x)) == get_reachable(query, graph, edges));
 // assert(get_reachable_on_path(query, father, lvl, dsu) == get_reachable_on_path_brute(query, graph, edges));
  return get_reachable(query, graph, edges) - get_reachable_on_path_brute(query, graph, edges) >= query.count;
}

int main(){

  int n, q;

  scanf("%d %d", &n, &q);

  assert(1 <= n && n <= 1e5);
  assert(1 <= q && q <= 1e5);

  vector<query_t> queries;
  vector<vector<int> > graph(n + 1, vector<int>());
  vector<int> lvl(n + 1, 0);

  int __min = 0;
  int __max = 0;

  int lg = 0;
  while((1 << lg) <= n){
    lg++;
  }

  vector<vector<int> > father(lg + 1, vector<int>(n + 1, 0));

  map<pair<int,int>, int> edges;

  for(int i = 1;i < n;i++){
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    assert(1 <= x && x <= n);
    assert(1 <= y && y <= n);
    assert(0 <= z && z <= 1e9);
    graph[x].push_back(y);
    graph[y].push_back(x);
    edges[{x,y}] = z;
    edges[{y,x}] = z;
    queries.push_back(query_t(x, y, 0, 0, z, z, -1));
    __min = min(__min, z);
    __max = max(__max, z);
  }

  dfs(1, 0, graph, father, lvl);

  for(int h = 1;h <= lg;h++){
    for(int i = 1;i <= n;i++){
      father[h][i] = father[h - 1][father[h - 1][i]];
    }
  }


  
  for(int i = 0;i < q;i++){
    int x, y, count;
    scanf("%d %d %d", &x, &y, &count);
    assert(0 <= count && count <= n);
    queries.push_back(query_t(x, y, count, lca(x, y, father, lvl), __min - 1, __max + 1, i));
  }
  
  DSU dsu(n);


  while(true){
    bool done = true;
    for(auto it:queries){
      if(it.dr - it.st > 1){
        done = false;
        break;
      }
    }

    if(done == true){
      break;
    }

    sort(queries.begin(), queries.end());
    dsu.reset();

    for(auto &it:queries){
      //printf("checking %d\n", it.mid());
      if(it.id == -1){
        dsu.unite(it.x, it.y);
      }else if(it.dr - it.st <= 1){
        continue;
      }else if(ok(it, father, lvl, dsu, graph, edges)){
        it.dr = it.mid();
      }else{
        it.st = it.mid();
      }
    }
  }

  vector<int> ans(q, 0);

  for(auto it:queries){
    if(it.id >= 0){
      ans[it.id] = it.dr;
    }
  }

  for(auto it:ans){
    assert(it <= __max);
    printf("%d ", (it == __max + 1 ? -1:it)); 
  }


  return 0;
}
