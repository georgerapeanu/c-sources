#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 9;

class DSU{
  int n;
  vector<int> father;
  vector<pair<int, int> > ops;
public:
  DSU(int n){
    this->n = n;
    this->father = vector<int>(n + 1, 0);
  }
  int find_root(int nod){
    if(father[nod] == 0){
      return nod;
    }
    return find_root(father[nod]);
  }

  bool unite(int x, int y){
    x = find_root(x);
    y = find_root(y);
    ops.push_back({x, father[x]});
    if(x == y){
      return false;
    }
    father[x] = y;
    return true;
  }

  void undo(){
    father[ops.back().first] = ops.back().second;
    ops.pop_back();
  }
};

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}


void backtracking(const int K, int pos, const vector<pair<int, int> > &edges, DSU &dsu, int comps, int mask, vector<int> &dp){
  if(pos >= (int)edges.size()){
    dp[mask] = 1;
    while(comps--){
      dp[mask] = mult(dp[mask],  K);
    }
    if(__builtin_popcount(mask) & 1){
      dp[mask] = sub(0, dp[mask]);
    }
    return ;
  }
  backtracking(K, pos + 1, edges, dsu, comps, mask, dp);
  bool tmp = dsu.unite(edges[pos].first, edges[pos].second);
  backtracking(K, pos + 1, edges, dsu, comps - tmp, mask | (1 << pos), dp); 
  dsu.undo();
}

int main(){

  
  int n, m, k;
  
  cin >> n >> m >> k;

  vector<vector<int> > graph(n + 1, vector<int>());
  vector<pair<int ,int> > edges(m);


  for(int i = 0;i < m;i++){
    cin >> edges[i].first >> edges[i].second;
  }
 
  DSU dsu(n);
  vector<int> dp(1 << m, 0);

  backtracking(k, 0, edges, dsu, n, 0, dp);

  for(int i = 0;i < m;i++){
    for(int conf = (1 << m) - 1;conf >= 0;conf--){
      if(!((conf >> i) & 1)){
        dp[conf] = add(dp[conf], dp[conf ^ (1 << i)]);
      }
    }
  }

  vector<int> fr(m + 1, 0);

  for(int conf = 0;conf < (int)dp.size();conf++){
    int tmp = __builtin_popcount(conf);
    if(tmp & 1){
      dp[conf] = sub(0, dp[conf]);
    }
    fr[tmp] = add(fr[tmp], dp[conf]);
  }

  for(auto it:fr){
    cout << it << " ";
  }


  return 0;
}
