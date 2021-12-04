#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n;
vector<int> graph[NMAX + 5];
int dp[NMAX + 5];

void predfs(int nod,int tata){
  dp[nod] = 1e9;
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    predfs(it,nod);
    dp[nod] = min(dp[nod],dp[it]);
  }

  if(tata != 0 && graph[nod].size() == 1){
    dp[nod] = min(dp[nod], nod);
  }
}

bool cmp(int a,int b){
  return dp[a] < dp[b];
}

void get_liniarizare(int nod,int tata,vector<int> &ans){
  sort(graph[nod].begin(),graph[nod].end(),cmp);
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    get_liniarizare(it,nod,ans);
  }
  ans.push_back(nod);
}

inline bool better(const vector<int> &a, const vector<int> &b){
  for(int i = 0;i < (int)a.size();i++){
    if(a[i] != b[i]){
      return a[i] < b[i];
    }
  }
  return false;
}

bool cmp2(int a,int b){
  return graph[a].size() < graph[b].size();
}

int main(){

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  scanf("%d",&t);
  while(t--){

    scanf("%d",&n);
    
    
    vector<int> nodes;
    vector<int> order;
    
    for(int i = 1;i <= n;i++){
      graph[i].clear();
      order.push_back(i);
    }

    for(int i = 1;i < n;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      graph[x].push_back(y);
      graph[y].push_back(x);
    }
    
    sort(order.begin(),order.end(), cmp2);

    for(int i = 0;i < n;i++){
      if(i < 70 || i > n - 70){
        nodes.push_back(order[i]);
      }
    }

    vector<int> ans;
    vector<int> tmp;
    for(auto it:nodes){
      tmp.clear();
      predfs(it,0);
      get_liniarizare(it,0,tmp);

      if(ans.empty()){
        swap(ans,tmp);
      }else if(better(tmp,ans)){
        swap(ans,tmp);
      }
    }

    for(auto it:ans){
      printf("%d ",it);
    }
    printf("\n");
  }

    return 0;
}
