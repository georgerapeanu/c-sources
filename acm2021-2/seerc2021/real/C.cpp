#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3000;
const int MOD = 998244353;

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

int n;
vector<int> graph[NMAX + 5];

int color[NMAX + 5];
int st[NMAX + 5];
int dr[NMAX + 5];
int dp[NMAX + 5][2 * NMAX + 5];
int tmp_dp[2 * NMAX + 5];
int tmp_st;
int tmp_dr;
int fr[NMAX + 5];

void dfs(int nod,int tata,int target){

  st[nod] = dr[nod] = NMAX;
  dp[nod][NMAX] = 0;

  if(color[nod] == target){
    dr[nod]++;
    dp[nod][dr[nod]] = 1;
  }else{
    st[nod]--;
    dp[nod][st[nod]] = 1;
  }


  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it,nod,target);
    tmp_st = st[nod] + st[it] - NMAX;
    tmp_dr = dr[nod] + dr[it] - NMAX;
    if(tmp_st - NMAX < -fr[target]){
      tmp_st = NMAX - fr[target];
    }
    for(int j = tmp_st;j <= tmp_dr;j++){
      tmp_dp[j] = 0;
    }
    for(int j = st[nod];j <= dr[nod];j++){
      for(int k = st[it];k <= dr[it];k++){
        tmp_dp[j + k - NMAX] = add(tmp_dp[j + k - NMAX],mult(dp[nod][j],dp[it][k]));
      }
    }
    for(int j = tmp_st;j <= tmp_dr;j++){
      if(st[nod] <= j && j <= dr[nod]){
        dp[nod][j] = add(dp[nod][j], tmp_dp[j]);
      }else{
        dp[nod][j] = add(0, tmp_dp[j]);
      }
    }
    st[nod] = tmp_st;
    dr[nod] = tmp_dr;
  }
}

int main(){

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d", &color[i]);
    fr[color[i]]++;
  }

  for(int i = 1;i < n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  int ans = 0;

  for(int c = 1;c <= n;c++){
    dfs(1,0,c);
    for(int i = 1;i <= n;i++){
      for(int j = NMAX + 1;j <= dr[i];j++){
        ans = add(ans, dp[i][j]);
      }
    }
  }

  printf("%d\n",ans);

  return 0;
}
