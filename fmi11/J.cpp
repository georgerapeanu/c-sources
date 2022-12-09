#include <bits/stdc++.h>

using namespace std;

class DSU{

  int n;
  vector<int> father;
  vector<int> color;
  vector<vector<pair<int, int> > > elems;
public:

  DSU(int n){
    this->n = n;
    father = vector<int>(n + 1, 0);
    color = vector<int>(n + 1, 0);
    elems = vector<vector<pair<int, int > > >(n + 1, vector<pair<int, int >>());

    for(int i = 1;i <= n;i++){
      elems[i].push_back({i, 0});
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
    
    if(color[x] == color[y]){
      if(elems[x].size() < elems[y].size()){
        for(auto &it:elems[x]){
          it.second ^= 1;
        }
        color[x] ^= 1;
      } else {
        for(auto &it:elems[y]){
          it.second ^= 1;
        }
        color[y] ^= 1;
      }
    }

    if(elems[x].size() > elems[y].size()){
      elems[x].swap(elems[y]);
    }

    for(auto it:elems[x]){
      elems[y].push_back(it);
    }
    father[x] = y;

    return true;
  }
};

int main(){
  
  int n, m;
  scanf("%d %d", &n, &m);
  
  DSU dsu(n + m);

  vector<int> a(n + 1, 0);

  for(int i = 1;i <= n;i++){
    scanf("%d", &a[i]);
  }

  vector<int> last(256, -1);
  vector<int> next(n + 1, -1);
  
  for(int i = 1;i <= n;i++){
    for(int j = 1;j < 256;j <<= 1){
      if(last[a[i] ^ j] != -1 && next[last[a[i] ^ j]] == -1){
        next[last[a[i] ^ j]] = i;
        dsu.unite(last[a[i] ^ j], i);
      }
    }
  }

  while(m--){
    int t, v;
    scanf("%d %d", &t, &v);
    if(t == 1){
      a.push_back(v);
      next.push_back(-1);
      for(int j = 1;j < 256;j <<= 1){
        if(last[a.back() ^ j] != -1 && next[last[a.back() ^ j]] == -1){
          next[last[a.back() ^ j]] = (int)a.size() - 1;
          dsu.unite(last[a.back() ^ j], (int)a.size() - 1);
        }
      }
    } else {
      printf(dsu.query(v) ? "Mario":"Ion"); 
    }
  }

  return 0;
}
