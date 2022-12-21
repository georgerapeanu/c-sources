#include <bits/stdc++.h>

using namespace std;


vector<int> dfs(int nod, int tata, const vector<vector<int> > &graph, vector<int> &lvl, vector<int> &currentCycle){
  lvl[nod] = 1 + lvl[tata];

  bool hasBackEdge = 0;

  for(auto it:graph[nod]){
    if(it == tata){
      continue; 
    }
    
  }
}

int main(){

  int n, m;

  scanf("%d %d", &n, &m);

  vector<vector<int> > graph(n + 1);

  for(int i = 1;i <= m;i++){
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  vector<int> lvl(n + 1, 0);

  dfs(1, 0, graph, lvl);

  return 0;
}
