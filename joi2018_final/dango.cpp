#include <bits/stdc++.h>

using namespace std;

class BipartiteMatcher{
  int n, m;
  vector<int> l;
  vector<int> r;
  vector<vector<int> > graph;
  vector<bool> viz;

  bool pairup(int nod){
    if(viz[nod] == true){
      return false;
    }
    viz[nod] = true;
    for(auto it:graph[nod]){
      if(r[it] == -1){
        l[nod] = it;
        r[it] = nod;
        return true;
      }
    }
    for(auto it:graph[nod]){
      if(pairup(r[it])){
        l[nod] = it;
        r[it] = nod;
        return true;
      }
    }
    return false;
  }

  public:

  BipartiteMatcher(int n, int m) {
    this->n = n;
    this->m = m;
    this->l = vector<int>(n, -1);
    this->r = vector<int>(m, -1);
    this->graph = vector<vector<int> >(n, vector<int>());
    this->viz = vector<bool>(n, false);
  }

  void add_edge(int x, int y){
    graph[x].push_back(y);
  }

  int solve(){
    bool ok = true;

    while(ok){
      ok = false;
      for(int i = 0;i < n;i++){
        viz[i] = false;
      }
      for(int i = 0;i < n;i++){
        if(l[i] == -1 && pairup(i)){
          ok = true;
        }
      }
    }
    int cuplaj = 0;
    for(int i = 0;i < n;i++){
      cuplaj += (l[i] != -1);
    }
    return cuplaj;
  }
};

int main(){
  
    int n, m;
    cin >> n >> m;
    vector<string> v(n,"");
    vector<vector<int> > group(n, vector<int>(m, -1));

    for(int i = 0;i < n;i++){
      cin >> v[i];
    }

    int cnt_horizontal = 0;
    int cnt_vertical = 0;

    for(int i = 0;i < n;i++){
      for(int j = 0;j < m;j++){
        if(j + 2 < m && v[i][j] == 'R' && v[i][j + 1] == 'G' && v[i][j + 2] == 'W'){
          group[i][j] = cnt_horizontal;
          group[i][j + 1] = cnt_horizontal;
          group[i][j + 2] = cnt_horizontal;
          cnt_horizontal++;
        }
        if(i + 2 < n && v[i][j] == 'R' && v[i + 1][j] == 'G' && v[i + 2][j] == 'W'){
          cnt_vertical++;
        }
      }
    }
    
    BipartiteMatcher matcher(cnt_horizontal, cnt_vertical);
    
    int last_vertical = 0;
    for(int i = 0;i < n;i++){
      for(int j = 0;j < m;j++){
        if(i + 2 < n && v[i][j] == 'R' && v[i + 1][j] == 'G' && v[i + 2][j] == 'W'){
          if(group[i][j] != -1){
            matcher.add_edge(group[i][j], last_vertical);
          }
          if(group[i + 1][j] != -1){
            matcher.add_edge(group[i + 1][j], last_vertical);
          }
          if(group[i + 2][j] != -1){
            matcher.add_edge(group[i + 2][j], last_vertical);
          }
          last_vertical++;
        }
      }
    }


    printf("%d", cnt_horizontal + cnt_vertical - matcher.solve());
    
    return 0;
}
