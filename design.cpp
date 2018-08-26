#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
 
using namespace std;
FILE *f = fopen("design.in","r");
FILE *g = fopen("design.out","w");
 
template <class T> class flow_graph {
  public:
  static constexpr T eps = (T) 1e-9;
 
  struct edge {
    int to;
    T c;
    T f;
    int rev;
  };
 
  vector < vector <edge> > g;
  vector <int> ptr;
  vector <int> d;
  int n;
  int st, fin;
  bool modified;
    
  flow_graph(int n, int st, int fin) : n (n), st (st), fin (fin) {
    modified = true;
    g.resize(n);
    ptr.resize(n);
    d.resize(n);
  }
 
  void clear_flow() {
    modified = true;
    for (int i = 0; i < n; i++) {
      for (edge &e : g[i]) {
        e.f = 0;
      }
    }
  }
    
  void add(int from, int to, T forward_cap, T backward_cap) {
    modified = true;
    int from_size = g[from].size();
    int to_size = g[to].size();
    g[from].push_back({to, forward_cap, 0, to_size});
    g[to].push_back({from, backward_cap, 0, from_size});
  }
    
  bool expath() {
    queue <int> q({st});
    fill(d.begin(), d.end(), -1);
    d[st] = 0;
    while (!q.empty()) {
      int i = q.front();
      q.pop();
      for (edge &e : g[i]) {
        if (e.c > e.f + eps && d[e.to] == -1) {
          d[e.to] = d[i] + 1;
          if (e.to == fin) {
            return true;
          }
          q.push(e.to);
        }
      }
    }
    return false;
  }
    
  T dfs(int v, T w) {
    if (v == fin) {
      return w;
    }
    T r = 0;
    int j = ptr[v];
    while (j > 0) {
      j--;
      edge &e = g[v][j];
      if (e.c > e.f + eps && d[e.to] == d[v] + 1) {
        T ww = e.c - e.f;
        if (v != st) {
          ww = min(ww, w - r);
        }
        T t = dfs(e.to, ww);
        if (t > 0) {
          e.f += t;
          g[e.to][e.rev].f -= t;
          r += t;
          if (v != st && r >= w - eps) {
            return r;
          }
        }
      }
      ptr[v]--;
    }
    return r;
  }
 
  T flow;
 
  T max_flow() {
    if (!modified) {
      return flow;
    }
    modified = false;
    T ans = 0;
    while (expath()) {
      for (int i = 0; i < n; i++) {
        ptr[i] = g[i].size();
      }
      T add = dfs(st, -1);
      if (add <= eps) {
        break;
      }
      ans += add;
    }
    return flow = ans;
  }
 
  vector <bool> min_cut() {
    max_flow();
    vector <bool> ret(n);
    for (int i = 0; i < n; i++) {
      ret[i] = (d[i] != -1);
    }
    return ret;
  }
};
 
const int NMAX = 500;
int n,k;
bool viz[NMAX + 5];
vector<int> graph[NMAX + 5];
int colors[NMAX + 5][7];
int tmp_colors[NMAX + 5][7];
int ans[NMAX + 5];
int dp[NMAX + 5][7][7];
 
bool check(int nod,int tata){
    vector<int> sons;
    vector<int> pos_cols;
    for(auto it:graph[nod]){
        if(it != tata){
            check(it,nod);
            sons.push_back(it);
        }
    }
     
    if(ans[nod]){
        pos_cols.push_back(ans[nod]);
    }
    else{
        for(int i = 1;i <= k;i++){
            pos_cols.push_back(i);
        }
    }
     
    bool ok = 0;
     
    if(tata){
        for(int cul_tata = 1;cul_tata <= k;cul_tata++){
            if(colors[nod][cul_tata] == 0){
                continue;
            }
            colors[nod][cul_tata]--;
            for(auto cul:pos_cols){
                int S = 0,D = k + (int)sons.size() + 2;
                flow_graph<int> gg(k + (int)sons.size() + 5,S,D);
                for(int i = 0; i < (int)sons.size();i++){
                    gg.add(S,i + 1,1,0);
                    for(int col = 1;col <= k;col++){
                        if(dp[sons[i]][cul][col]){
                            gg.add(i + 1,col + (int)sons.size(),1,0);
                        }
                    }
                }
                for(int col = 1;col <= k;col++){
                    gg.add(col + (int)sons.size(),D,colors[nod][col],0);
                }
                 
                dp[nod][cul_tata][cul] = (gg.max_flow() == (int)sons.size());
                ok |= dp[nod][cul_tata][cul];
            }
            colors[nod][cul_tata]++;
        }
    }
    else{   
        for(auto cul:pos_cols){
            int S = 0,D = k + (int)sons.size() + 2;
            flow_graph<int> gg(k + (int)sons.size() + 5,S,D);
            for(int i = 0; i < (int)sons.size();i++){
                gg.add(S,i + 1,1,0);
                for(int col = 1;col <= k;col++){
                    if(dp[sons[i]][cul][col]){
                        gg.add(i + 1,col + (int)sons.size(),1,0);
                    }
                }
            }
            for(int col = 1;col <= k;col++){
                gg.add(col + (int)sons.size(),D,colors[nod][col],0);
            }
                         
             
            dp[nod][0][cul] = (gg.max_flow() == (int)sons.size());
            ok |= dp[nod][0][cul];
        }
    }
    return ok;
}
 
bool ok(){
    memset(dp,0,sizeof(dp));
    return check(1,0);
}
 
void dfs(int nod,int tata){
    int child = -1;
    for(auto it:graph[nod]){
        if(it != tata){
            dfs(it,nod);
            if(!ans[it]){
                child = it;
            }
        }
    }
 
    if(child != -1){
        for(int i = 1;i <= k;i++){
            if(tmp_colors[child][i]){
                ans[nod] = i;
                for(auto it:graph[nod]){
                    tmp_colors[it][i]--;
                }
                break;
            }
        }
    }
}
 
int main(){
    fscanf(f,"%d %d",&n,&k);
    for(int i = 1;i <= n;i++){
        int sz;
        fscanf(f,"%d",&sz);
        for(int j = 1;j <= sz;j++){
            int col;
            fscanf(f,"%d",&col);
            colors[i][col]++;
            tmp_colors[i][col]++;
        }
        for(int j = 1;j <= sz;j++){
            int to;
            fscanf(f,"%d",&to);
            graph[i].push_back(to);
        }
    }
 
    dfs(1,0);
     
    for(int i = 1;i <= n;i++){
        if(ans[i]){
            continue;
        }
        for(int j = 1;j <= k;j++){
            ans[i] = j;
            if(j == k || ok()){
                break;
            }
        }
    }
 
    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",ans[i]);
    }
 
    return 0;
}