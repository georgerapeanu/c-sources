#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("hamster.in","r");
FILE *g = fopen("hamster.out","w");

const int LEN = 1 << 20;
char buff[LEN];
int ind = LEN - 1;

int i32(){
  int ans = 0;
  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,f);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,f);
    }
  }
  return ans;
}

struct query_t{
  int d;
  int k;
  int id;
  int l, r;
  
  bool operator < (const query_t &other)const{
    if(d != other.d){
      return d < other.d;
    }
    return id < other.id;
  }
};


int main(){
  
  int n, m;
  n = i32();
  m = i32();

  vector<int> v(n, 0);

  for(auto &it:v){
    it = i32();
  }

  vector<query_t> queries;
  
  for(int i = 0;i < m;i++){
    int k, d;
    k = i32();
    d = i32();
    queries.push_back({d, k, i, 0, 0});
  }

  for(int i = 0;i < n;i++){
    for(int j = i + 1;j < n;j++){
      queries.push_back({v[j] - v[i], -1, -1, i, j});
    }
  }

  sort(queries.begin(),queries.end());

  vector<int> ans(m, 0);
  vector<int> nxt(n + 1, 0);
  vector<int> dist(n + 1, 0);

  for(int i = 0;i <= n;i++){
    nxt[i] = i + 1;
    dist[i] = i;
  }

  for(auto it:queries){
    if(it.id < 0){
      nxt[it.l] = it.r + 1;
      int nod = it.l;
      while(nxt[nod] <= n && dist[nxt[nod]] > dist[nod] + 1){
        dist[nxt[nod]] = dist[nod] + 1;
        int tmp = nxt[nod];
        while(tmp > 0 && dist[tmp - 1] > dist[tmp]){
          dist[tmp - 1] = dist[tmp];
          tmp--;
        }
        nod = nxt[nod];
      }
    }else{
      ans[it.id] = dist[it.k];
    }
  }

  for(int i = 0;i < m;i++){
    fprintf(g, "%d\n", ans[i]);
  }

  fclose(f);
  fclose(g);
 
  return 0;
}

