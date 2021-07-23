#include <bits/stdc++.h>

using namespace std;

class TopologicalSorter{
  int n;
  vector<vector<int> > graph;
  vector<pair<int,int> > edges;
  vector<int> gr;

public:

  TopologicalSorter(int n){
    this->n = n;
    graph = vector<vector<int> >(n + 5,vector<int>());
    edges = vector<pair<int,int> > ();
    gr = vector<int>(n + 5,0);
  }

  void addEdge(int x,int y){
    edges.push_back({x,y});
    graph[x].push_back(y);
    gr[y]++;
  }

  vector<int> solve(){
    gr = vector<int>(n + 5,0);
    for(auto it:edges){
      gr[it.second]++;
    }
    vector<int> ans;
    for(int i = 0;i < n;i++){
      if(gr[i] == 0){
        ans.push_back(i);
      }
    }
    for(int i = 0;i < (int)ans.size();i++){
      int nod = ans[i];
      for(auto it:graph[nod]){
        gr[it]--;
        if(gr[it] == 0){
          ans.push_back(it);
        }
      }
    }
    return ans;
  }
};

int n,m,k;
vector<vector<int>> v;
vector<int> row_color;
vector<int> col_color;

vector<int> best;

vector<vector<int> > my_v;

void updateBest(vector<int> &ans,vector<int> &nope){
  vector<int> pr_ans;
  for(auto it:ans){
    if(nope[it] == false){
      if(it < n){
        pr_ans.push_back(-(it + 1));
      }else{
        pr_ans.push_back(it - n + 1);
      }
    }
  }

  if(best.empty() || best.size() > pr_ans.size()){
    best = pr_ans;
  }
}

void printBest(){
  if(best.empty()){
    printf("-1\n");
    return ;
  }

  my_v = vector<vector<int> >(n,vector<int>(m,-1));

  printf("%d\n",(int)best.size());
  for(auto it:best){
    printf("%d\n",it);
  }
  return ;
}

int main(){

  scanf("%d %d %d",&n,&m,&k);

  v = vector<vector<int> > (n,vector<int>(m,0));

  row_color = vector<int>(n,0);
  col_color = vector<int>(m,0);

  vector<bool> taken(n + m,false);

  for(auto &it:row_color){
    scanf("%d",&it);
  }
  
  for(auto &it:col_color){
    scanf("%d",&it);
  }

  for(int i = 0;i < n;i++){
    for(int j = 0;j < m;j++){
      scanf("%d",&v[i][j]);
      if(v[i][j] != row_color[i] && v[i][j] != col_color[j]){
        printBest();
        return 0;
      }
    }
  }

  TopologicalSorter checker(n + m);
  vector<int> nope;
  vector<int> ans;

  nope = vector<int>(n + m,0);

  ///lines only

  for(int j = 0;j < m;j++){
    bool ok = true;
    for(int i = 0;i < n;i++){
      ok &= (v[i][j] == row_color[i]);
    }
    if(ok == false){
      for(int i = 0;i < n;i++){
        if(row_color[i] == col_color[j]){
          ;
        }else if(v[i][j] == col_color[j]){
          checker.addEdge(i,j + n);
        }else{
          checker.addEdge(j + n,i);
        }
      }
    }else{
      nope[j + n] = 1;
    }
  }

  ans = checker.solve();

  if(ans.size() == n + m){
    updateBest(ans,nope);
  }

  ///cols only
  
  checker = TopologicalSorter(n + m);
  nope = vector<int>(n + m,0);

  for(int i = 0;i < n;i++){
    bool ok = true;
    for(int j = 0;j < m;j++){
      ok &= (v[i][j] == col_color[j]);
    }
    if(ok == false){
      for(int j = 0;j < m;j++){
        if(row_color[i] == col_color[j]){
          ;
        }else if(v[i][j] == row_color[i]){
          checker.addEdge(j + n,i);
        }else{
          checker.addEdge(i,j + n);
        }
      }
    }else{
      nope[i] = true;
    }
  }
  
  ans = checker.solve();

  if(ans.size() == n + m){
    updateBest(ans,nope);
  }

  printBest();

  return 0;
}
