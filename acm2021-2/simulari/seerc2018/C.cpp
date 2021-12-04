#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;
const int inf = 1e9;

int n,m;
int type[NMAX + 5];
int dp[NMAX + 5][NMAX + 5];
int len[NMAX + 5];
int tmp_len;
int tmp[NMAX + 5];

vector<int> graph[NMAX + 5];

bool dfs(int nod,int tata,int limit){
  if(type[nod] == 0){
    len[nod] = 0;
    dp[nod][0] = 0;
  }else{
    len[nod] = 1;
    dp[nod][0] = 0;
    dp[nod][1] = 0;
  }
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    if(dfs(it,nod,limit)){
      return true;
    }
    
    tmp_len = min(m,len[nod] + len[it]);
    for(int j = 0;j <= tmp_len;j++){
      tmp[j] = inf;
    }

    for(int j = 0;j <= len[nod];j++){
      for(int k = 0;k <= len[it];k++){
        if(j == 0){
          if(dp[it][k] + 1 <= limit){
            tmp[j + k] = min(tmp[j + k],dp[it][k] + 1);
          }
          continue;
        }
        if(k == 0){
          tmp[j + k] = min(tmp[j + k],dp[nod][j]);
          continue;
        }
        if(dp[nod][j] + 1 + dp[it][k] <= limit){
          tmp[j + k] = min(tmp[j + k],max(dp[nod][j],dp[it][k] + 1));
        }
      }
    }

    len[nod] = tmp_len;
    for(int j = 0;j <= tmp_len;j++){
      dp[nod][j] = tmp[j];
    }
  }

  return (len[nod] >= m && dp[nod][m] < inf);
}

void debug(int limit){
  printf("limit %d\n",limit);
  for(int i = 1;i <= n;i++){
    printf("debuging %d with len %d: ",i,len[i]);
    for(int j = 0;j <= len[i];j++){
      printf("%d ",dp[i][j]);
    }
    printf("\n");
  }
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
      scanf("%d",&type[i]);
    }

    for(int i = 1;i < n;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      graph[x].push_back(y);
      graph[y].push_back(x);
    }

    int st = -1;
    int dr = n + 1;

    while (dr - st > 1){
      int mid = (st + dr) / 2;

      if(dfs(1,0,mid)){
        dr = mid;
      }else{
        st = mid;
      }
    //  debug(mid);
    }
  
    printf("%d\n",dr);

    return 0;
}
