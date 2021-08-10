#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MOD = 998244353;

int t;
int n;
vector<int> graph[NMAX + 5];
int cnt[NMAX + 5];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int dfs(int nod,int father,int k){
  int cnt = 0;
  for(auto it:graph[nod]){
    if(it == father){
      continue;
    }
    int tmp = dfs(it,nod,k);
    if(tmp == 0){
      return 0;
    }
    if(tmp == 2){
      cnt++;
      if(cnt >= k){
        cnt -= k;
      }
    }
  }
  if(cnt == 0){
    return 2;
  }
  if(cnt == k - 1){
    return 1;
  }
  return 0;
}

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d",&n);
    for(int i = 1;i < n;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      graph[x].push_back(y);
      graph[y].push_back(x);
    }

    cnt[1] = 1;
    for(int i = 1;i < n;i++){
      cnt[1] = add(cnt[1],cnt[1]);
    }

    for(int i = 2;i <= n;i++){
      if((n - 1) % i != 0){
        continue;
      }
      cnt[i] = (dfs(1,0,i) == 2);
    }

    for(int i = n;i;i--){
      for(int j = 2 * i;j <= n;j += i){
        cnt[i] = scad(cnt[i],cnt[j]);
      }
    }

    for(int i = 1;i <= n;i++){
      printf("%d ",cnt[i]);
    }
    printf("\n");

    for(int i = 1;i <= n;i++){
      cnt[i] = 0;
      graph[i].clear();
    }
  }

  return 0;
}
