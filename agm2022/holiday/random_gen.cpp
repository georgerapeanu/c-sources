#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int get_lca(int u, int v, const vector<int> &lvl, const vector<vector<int> > &father){
  if(lvl[u] > lvl[v]){
    swap(u, v);
  }

  for(int h = (int)father.size() - 1;h >= 0;h--){
    if((1 << h) <= lvl[v] - lvl[u]){
      v = father[h][v];
    }
  }

  if(v == u){
    return u;
  }
  
  for(int h = (int)father.size() - 1;h >= 0;h--){
    if(father[h][u] != father[h][v]){
      u = father[h][u];
      v = father[h][v];
    }
  }

  return father[0][u];
}

void dfs(int nod, int tata, vector<vector<int> > &graph, vector<int> &lvl, vector<vector<int> > &father){
  father[0][nod] = tata;
  lvl[nod] = 1 + lvl[tata];
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it, nod, graph, lvl, father);
  }
}

int get_count(int u, int v, const vector<int> &lvl, const vector<vector<int> > &father){
  return lvl[u] + lvl[v] - 2 * lvl[get_lca(u, v, lvl, father)] + 1;
}

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int vmax = opt<int>("vmax");
  int q = opt<int>("q");
 
  printf("%d %d\n", n, q);

  vector<vector<int> > graph(n + 1, vector<int>());
  vector<int> lvl(n + 1, 0);

  int lg = 1;
  while((1 << lg) <= n){
    lg++;
  }

  vector<vector<int> > father(lg + 1, vector<int>(n + 1, 0));


  for(int i = 2;i <= n;i++){
    int u = i;
    int v = rnd.next(1, i - 1);
    int cost = rnd.next(0, vmax);
    printf("%d %d %d\n", u, v, cost);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs(1, 0, graph, lvl, father);

  for(int h = 1;h <= lg;h++){
    for(int i = 1;i <= n;i++){
      father[h][i] = father[h - 1][father[h - 1][i]];
    }
  }

  for(int i = 1;i <= q;i++){
    int u = -1, v = -1, count = -1;

    while(true){
      u = rnd.next(1, n);
      v = rnd.next(1, n);
      if(get_count(u,v, lvl, father) != n){
        count = rnd.next(1, n - get_count(u, v, lvl, father));
        break;
      }
    }

    printf("%d %d %d\n", u, v, count);
  }
  return 0;

}
