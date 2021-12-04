#include <bits/stdc++.h>

using namespace std;

struct edge_t{
  int x,y,s;

  bool operator < (const edge_t &other)const{
    return s < other.s;
  }
};

class DSU{
  int n;
  vector<int> father;
  vector<int> weight;

public:

  DSU(int n){
    this->n = n;
    this->father = vector<int>(n + 1,0);
    this->weight = vector<int>(n + 1,0);
  }

  int find_root(int nod){
    if(father[nod] == 0){
      return nod;
    }
    return father[nod] = find_root(father[nod]);
  }

  bool unite(int x,int y){
    x = find_root(x);
    y = find_root(y);
    if(x == y){
      return false;
    }

    if(weight[x] > weight[y]){
      swap(x,y);
    }
    weight[y] += weight[x];
    father[x] = y;

    return true;
  }
};

int main(){
    int t;
    int n,m,k;

    scanf("%d",&t);

    for(int test = 1;test <= t;test++){
      scanf("%d %d %d",&n,&m,&k);

      vector<edge_t> edges;
      vector<edge_t> lower_edges;

      for(int i = 1;i <= m;i++){
        edge_t tmp;
        scanf("%d %d %d",&tmp.x,&tmp.y,&tmp.s);
        edges.push_back(tmp);
        if(tmp.s <= k){
          lower_edges.push_back(tmp);
        }
      }

      sort(edges.begin(),edges.end());
      sort(lower_edges.begin(),lower_edges.end());
      reverse(lower_edges.begin(),lower_edges.end());

      DSU dsu(1);
      
      long long ans = 1e18;
      dsu = DSU(n);

      int first_cost = -1;
      int cnt = 0;

      for(auto it:lower_edges){
        if(dsu.unite(it.x,it.y)){
          if(first_cost == -1){
            first_cost = it.s;
          }
          cnt++;
        }
      }
      
      if(cnt == n - 1){
        ans = min(ans,1LL * k - first_cost); 
      }
     
      dsu = DSU(n);
      long long local_ans = 0;
      bool found = false;

      for(auto it:edges){
        if(dsu.unite(it.x,it.y)){
          local_ans += (max(0,it.s - k));
          if(it.s >= k){
            found = true;
          }
        }
      }
      if(found == false){
        for(auto it:edges){
          if(it.s >= k){
            local_ans = it.s - k;
            found = true;
            break;
          }
        }
        if(found){
          ans = min(ans,local_ans);
        }
      }else{
        ans = min(ans,local_ans);
      }
      printf("%lld\n",ans);
    }

    return 0;
}
