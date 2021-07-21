#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int father[NMAX + 5];
int weight[NMAX + 5];

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

  father[x] = y;
  weight[y] += weight[x];
  
  return true;
}

int t;
int n;
pair<int,int> v[NMAX + 5];

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d",&n);

    priority_queue<int> pq;
    for(int i = 1;i <= n;i++){
      father[i] = 0;
      weight[i] = 1;
      pq.push(1);
    }

    for(int i = 1;i <= n;i++){
      scanf("%d",&v[i].first);
      v[i].second = i;
    }
    sort(v + 1,v + 1 + n);

    bool ok = true;
    bool active_n = true;

    for(int i = 1;i <= n;i++){
      if(weight[v[i].second] != pq.top()){
        ok = false;
      }
      if(v[i].second == n){
        active_n = false;
      }
      pq.pop();
      unite(v[i].second,v[i].second + 1);
      if(find_root(v[i].second) < n || find_root(v[i].second) == n && active_n == true){
        pq.push(weight[find_root(v[i].second)]);
      }
    }

    printf(ok ? "Yes\n":"No\n");
  }

    return 0;
}
