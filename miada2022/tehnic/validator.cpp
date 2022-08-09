#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int VMAX = 1e9;

int dfs(int nod, int father, vector<vector<int> >& graph, vector<int>& viz){
  if(viz[nod]){
    return -1;
  }
  viz[nod] = 1;

  int sum = 1;

  for(auto it:graph[nod]){
    if(it == father){
      continue;
    }
    int tmp = dfs(it, nod, graph, viz);
    if(tmp == -1){
      return -1;
    }
    sum += tmp;
  }
  return sum;
}

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(2, NMAX,"n");
  inf.readEoln();

  vector<vector<int> > graph(n + 1, vector<int>());

  for(int i = 1;i < n;i++){
    int x, y, z;
    x = inf.readInt(1, n, "x_i");
    inf.readSpace();
    y = inf.readInt(1, n, "y_i");
    inf.readSpace();
    z = inf.readInt(0, VMAX, "z_i");
    graph[x].push_back(y);
    graph[y].push_back(x);
    inf.readEoln();
  }
  int q = inf.readInt(1, QMAX,"q");
  inf.readEoln();
  for(int i = 0;i < q;i++){
    int t, x, y;
    t = inf.readInt(0, 1, "t_i");
    inf.readSpace();
    x = inf.readInt(1, n, "x_i");
    inf.readSpace();
    y = inf.readInt(1, n, "y_i");
    if(t == 0){
      inf.readSpace();
      int z = inf.readInt(0, VMAX, "z_i");
    }
    inf.readEoln();
  }
  inf.readEof();

  vector<int> viz(n + 1, 0);
  ensuref(dfs(1, 0, graph, viz) == n, "Graph is not a tree");

  return 0;
}


