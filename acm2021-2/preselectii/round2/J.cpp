#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
int t;
int n,m;
vector<int> graph[NMAX + 5];
bool inst[NMAX + 5];
int st[NMAX + 5];
int len;
int low[NMAX + 5];
int id[NMAX + 5];
int last_id;
int ctc[NMAX + 5];
int last_ctc;

vector<int> compressed_graph[NMAX + 5];

class MatchingSolver{
  int n,m;
  vector<vector<int> > graph;
  vector<int> l,r;
  vector<int> viz;

  bool pairup(int nod){
    if(viz[nod]){
      return false;
    }
    viz[nod] = true;

    for(auto it:graph[nod]){
      if(r[it] == 0){
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
 
  MatchingSolver(int n,int m){
    this->n = n;
    this->m = m;
    this->graph = vector<vector<int> >(n + 1,vector<int>());
    l = vector<int>(n + 1,0);
    r = vector<int>(m + 1,0);
    viz = vector<int>(n + 1,0);
  }

  void addEdge(int x,int y){
    graph[x].push_back(y);
  }

  int getMatching(){
    bool ok = true;
    int ans = 0;
    while(ok){
      ok = false;
      for(int i = 1;i <= n;i++){
        viz[i] = 0;
      }
      for(int i = 1;i <= n;i++){
        if(l[i] == 0 && pairup(i)){
          ok = true;
          ans++;
        }
      }
    }
    return ans;
  }
};

void dfs(int nod){
  st[++len] = nod;
  inst[nod] = true;
  id[nod] = low[nod] = ++last_id;
  for(auto it:graph[nod]){
    if(id[it] == 0){
      dfs(it);
    }
    if(inst[it]){
      low[nod] = min(low[nod],low[it]);
    }
  }

  if(low[nod] == id[nod]){
    last_ctc++;
    while(st[len] != nod){
      ctc[st[len]] = last_ctc;
      inst[st[len]] = false;
      len--;
    }
    ctc[st[len]] = last_ctc;
    inst[st[len]] = false;
    len--;
  }
}

int viz[NMAX + 5];
void addEdgeDfs(MatchingSolver &solver,int root,int nod){
  viz[nod] = root;
  if(root != nod){
    solver.addEdge(root,nod);
  }
  for(auto it:compressed_graph[nod]){
    if(viz[it] != root){
      addEdgeDfs(solver,root,it);
    }
  }
}

const int LEN = 1 << 12;
int ind = LEN - 1;
char buff[LEN];

int i32(){
  int ans = 0;
  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }

  return ans;
}

int main(){

  t = i32();
  
  for(int test = 1;test <= t;test++){
    n = i32();
    m = i32();

    last_id = last_ctc = 0;
    len = 0;
    for(int i = 1;i <= n;i++){
      graph[i].clear();
      compressed_graph[i].clear();
      inst[i] = false;
      ctc[i] = 0;
      low[i] = id[i] = 0;
      viz[i] = 0;
    }

    for(int i = 1;i <= m;i++){
      int x,y;
      x = i32();
      y = i32();
      graph[x].push_back(y);
    }

    for(int i = 1;i <= n;i++){
      if(ctc[i]){
        continue;
      }
      dfs(i);
    }

    for(int i = 1;i <= n;i++){
      for(auto it:graph[i]){
        if(ctc[i] != ctc[it]){
          compressed_graph[ctc[i]].push_back(ctc[it]);
        }
      }
    }

    MatchingSolver solver(last_ctc,last_ctc);

    for(int i = 1;i <= last_ctc;i++){
      addEdgeDfs(solver,i,i);
    }
    printf("Case %d: %d\n",test,last_ctc - solver.getMatching());
  }

  return 0;
}
