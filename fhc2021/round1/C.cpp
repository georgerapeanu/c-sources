#include <bits/stdc++.h>

using namespace std;

const int NMAX = 8e5;
const int CMAX = 20;
const int MOD = 1e9 + 7;

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

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int t;
int n;
vector<pair<int,int>> graph[NMAX + 5];
int dpDown[NMAX + 1][CMAX + 1];
int dpUp[NMAX + 1][CMAX + 1];

void predfs(int nod,int tata){
  dpDown[nod][CMAX] = 1;
  for(auto it:graph[nod]){
    if(it.first == tata){
      continue;
    }
    predfs(it.first,nod);
    for(int j = 0;j <= CMAX;j++){
      dpDown[nod][min(it.second,j)] += dpDown[it.first][j];
    }
  }
}

int defaultSum = 0;
int ans = 0;

void dfs(int nod,int tata,int cost){
  dpUp[nod][CMAX] += 1;

  for(auto it:graph[nod]){
    if(it.first == tata){
      continue;
    }

    for(int j = 0;j <= CMAX;j++){
      dpUp[it.first][min(j,it.second)] += dpDown[nod][j];
      dpUp[it.first][min(j,it.second)] += dpUp[nod][j];
      dpUp[it.first][min(j,it.second)] -= dpDown[it.first][j];
    }
    dpUp[it.first][it.second]--;
    dfs(it.first,nod,it.second);
  }
  if(tata){
    int fuckedCosts = 0;
    for(int j = 0;j <= CMAX;j++){
      for(int k = 0;k <= CMAX;k++){
        fuckedCosts = add(fuckedCosts,mult(min(j,k),mult(scad(dpUp[nod][j],(j == CMAX)),dpDown[nod][k])));
      }
    }
    ans = mult(ans,scad(defaultSum,fuckedCosts));
  }

}


int dsuFather[NMAX + 5];
int dsuWeight[NMAX + 5];

int findRoot(int nod){
  if(dsuFather[nod] == 0){
    return nod;
  }
  return dsuFather[nod] = findRoot(dsuFather[nod]);
}

bool unite(int x,int y){
  x = findRoot(x);
  y = findRoot(y);

  if(x == y){
    return false;
  }

  if(dsuWeight[x] > dsuWeight[y]){
    swap(x,y);
  }

  dsuFather[x] = y;
  dsuWeight[y] += dsuWeight[x];
  return true;
}

int getWeight(int nod){
  return dsuWeight[findRoot(nod)];
}

int main(){

  scanf("%d",&t);

  for(int test = 1;test <= t;test++){
    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
      graph[i].clear();
      dsuFather[i] = 0;
      dsuWeight[i] = 1;
      for(int j = 0;j <= CMAX;j++){
        dpDown[i][j] = dpUp[i][j] = 0;
      }
    }

    vector<pair<int,pair<int,int> > > edges;

    for(int i = 1;i < n;i++){
      int a,b,c;
      scanf("%d %d %d",&a,&b,&c);

      graph[a].push_back({b,c});
      graph[b].push_back({a,c});

      edges.push_back({c,{a,b}});
    }

    defaultSum = 0;

    sort(edges.begin(),edges.end());
    reverse(edges.begin(),edges.end());

    for(auto it:edges){
      defaultSum = add(defaultSum,mult(it.first,mult(getWeight(it.second.first),getWeight(it.second.second))));
      unite(it.second.first,it.second.second);
    }

    ans = 1;
    predfs(1,0);
    dfs(1,0,0);

    printf("Case #%d: %d\n",test,ans);
  }

  return 0;
}
