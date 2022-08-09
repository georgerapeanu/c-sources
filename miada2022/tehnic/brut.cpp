#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}


int mult(int a ,int b){
  return 1LL * a * b % MOD;
}

void dfs(const vector<vector<pair<int ,int> >> &graph, vector<pair<int ,int> > &father, vector<int> &lvl, int nod){
  for(const auto &it:graph[nod]){
    if(it.first == father[nod].first){
      continue;
    }
    father[it.first] = make_pair(nod, it.second);
    lvl[it.first] = 1 + lvl[nod];
    dfs(graph, father, lvl, it.first);
  }
}

void update(vector<vector<pair<int, int> >> &graph, vector<pair<int, int> > &father, const vector<int>& lvl, int x, int y, int z){
  for(auto &it:graph[x]){
    if(it.first == y){
      it.second = z;
    }
  }
  for(auto &it:graph[y]){
    if(it.first == x){
      it.second = z;
    }
  }

  if(father[x].first == y){
    father[x].second = z;
  }else{
    father[y].second = z;
  }
}


int query(int n, const vector<pair<int, int> > &father, const vector<int> &lvl, int x, int y, vector<int> &marked){
  for(auto &it:marked){
    it = 0;
  }

  while(x != y){
    if(lvl[x] > lvl[y]){
      swap(x, y);
    }
    marked[y] = true;
    y = father[y].first;
  }


  int total_cost = 0;
  for(int i = 1;i <= n;i++){
    for(int j = i + 1;j <= n;j++){
      if(marked[i] == 1 && i != x){
        continue;
      }
      if(marked[j] == 1 && j != x){
        continue;
      }

      int u = i;
      int v = j;
      int cost = 0;

      while(u != v){
        if(lvl[u] > lvl[v]){
          swap(u, v);
        }

        if(marked[v] == 0){
          cost = add(cost, father[v].second);
        }
        v = father[v].first;
      }
      total_cost = add(total_cost, cost);
    }
  }
  return total_cost;
}

int main(){
  
  int n;

  scanf("%d", &n);

  vector<vector<pair<int, int> > > graph(n + 1, vector<pair<int, int> > ());
  vector<pair<int, int> > father(n + 1, make_pair(0, 0));
  vector<int> lvl(n + 1, 0);
  vector<int> marked(n + 1, 0);

  for(int i = 1;i < n;i++){
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    graph[x].push_back({y, z});
    graph[y].push_back({x, z});
  }

  lvl[1] = 1;
  dfs(graph, father, lvl, 1);

  int q;

  scanf("%d", &q);

  while(q--){
    int t, x, y;

    scanf("%d %d %d", &t, &x, &y);

    if(t == 0){ /// update
      int z;
      scanf("%d", &z);
      update(graph, father, lvl, x, y, z);
    }else if(t == 1){ /// query
      printf("%d\n", query(n, father, lvl, x, y, marked));
    }
  }

  return 0;
}
