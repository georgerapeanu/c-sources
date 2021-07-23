#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;

vector<pair<int,int> > graph[NMAX + 5];
bool inQ[NMAX + 5];
int cnt[NMAX + 5];
long long dist[NMAX + 5];
bool ok;

int t;
int n,m;

bool bellman(){
  queue<int> q;
  for(int nod = 1;nod <= n;nod++){
    cnt[nod] = 0;
    dist[nod] = 0;
    inQ[nod] = true;
    q.push(nod);
  }
  
  while(!q.empty()){
    int nod = q.front();
    q.pop();
    inQ[nod] = false;
    cnt[nod]++;
    if(cnt[nod] > 2 * (n + 1)){
      return false;
    }

    for(auto it:graph[nod]){
      if(dist[nod] + it.second < dist[it.first]){
        dist[it.first] = dist[nod] + it.second;
        if(inQ[it.first] == false){
          inQ[it.first] = true;
          q.push(it.first);
        }
      }
    }
  }

  long long _min = 0;
  for(int i = 1;i <= n;i++){
    _min = min(_min,dist[i]);
  }
  for(int i = 1;i <= n;i++){
    dist[i] -= _min;
  }
  return true;
}

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
      dist[i] = 1e18;
      inQ[i] = false;
      cnt[i] = 0;
      graph[i].clear();
    }

    for(int i = 1;i <= m;i++){
      int t,x,y,l;
      scanf("%d %d %d %d",&t,&x,&y,&l);
      x++;
      y++;
      if(t == 1){
        graph[y].push_back({x,-l});
      }else{
        graph[y].push_back({x,l});
      }
    }

    ok = bellman();
  

    if(!ok){
      printf("-1\n");
    }else{
      for(int i = 1;i <= n;i++){
        for(auto it:graph[i]){
          assert(dist[it.first] <= dist[i] + it.second);
        }
      }
     
      for(int i = 1;i <= n;i++){
        assert(0 <= dist[i] && dist[i] <= 1e12);
        printf("%lld ",dist[i]);
      }
      printf("\n");
    }

  }

  return 0;
}
