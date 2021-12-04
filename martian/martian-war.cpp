#include <bits/stdc++.h>

using namespace std;

class DSU {
  int n;
  vector<int> father;

public:
  
  DSU(int n) {
    this->n = n;
    this->father = vector<int>(n, -1);
  }

  int find_root(int nod) {
    if(father[nod] == -1) {
      return nod;
    }
    return father[nod] = find_root(father[nod]);
  }

  bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if(x == y){
      return false;
    }

    father[x] = y;
    
    return true;
  }

  void reset(){
    for(auto &it:this->father){
      it = -1;
    }
  }
};

struct query_t {
  int x, y;
  int id;

  query_t(){
    x = y = id = 0;
  }

  query_t(int x, int y, int id){
    this->x = x;
    this->y = y;
    this->id = id;
  }
};

const int NMAX = 250000;
vector<int> graph[NMAX + 1];
int lvl[NMAX + 1];
int father[NMAX + 1];
bool active[NMAX + 1];

void dfs(int nod, int tata){
  if(tata == -1){
     lvl[nod] = 0;
  }else{
    lvl[nod] = lvl[tata] + 1;
  }
  father[nod] = tata;

  for(auto it:graph[nod]){
    if(lvl[it] == -1){
      dfs(it, nod);
    }
  }
}

int process_edge(int x, int y, DSU &dsu){
    int count = 0;
    if(lvl[x] > lvl[y]){
      swap(x, y);
    }
    if(father[y] == x && active[y] == false){
      active[y] = true;
      count++;
    }else{
      while(dsu.find_root(x) != dsu.find_root(y)){
        x = dsu.find_root(x);
        y = dsu.find_root(y);
        if(lvl[x] > lvl[y]){
          swap(x, y);
        }
        dsu.unite(y, father[y]); 
        count--;
      }
    }

    return count;
}

FILE *f = fopen("martian-war.in","r");
FILE *g = fopen("martian-war.out","w");

const int LEN = 1 << 12;
int ind = LEN - 1;
char buff[LEN];

void reset_parse(){
  ind = LEN - 1;
  buff[ind] = 0;
}

int i32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, f);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, f);
    }
  }

  return ans;
}


int main(){
 
  int n, m, k;

  n = i32();
  m = i32();
  k = i32();

  for(int i = 0;i < n;i++){
    lvl[i] = -1;
  }

  DSU dsu(n);
  for(int i = 0;i < m + k;i++){
    int x, y;
    x = i32() - 1;
    y = i32() - 1;
    
    if(dsu.unite(x, y)){
      graph[x].push_back(y);
      graph[y].push_back(x);
    }
  }

  fclose(f);

  for(int i = 0;i < n;i++){
    if(lvl[i] == -1){
      dfs(i, -1);
    }
  }

  f = fopen("martian-war.in","r");
  reset_parse();
  dsu.reset();

  int count = 0;
  n = i32();
  m = i32();
  k = i32();
  for(int i = 0;i < m;i++){
    int x, y;
    x = i32() - 1;
    y = i32() - 1;
    count += process_edge(x, y, dsu);
  }

  while(k--){
    int x, y;
    x = i32() - 1;
    y = i32() - 1;
    count += process_edge(x, y, dsu);
    fprintf(g, "%d\n", count);
  }

  fclose(f);
  fclose(g);

  return 0;
}
