#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50;
const int inf = 1e9;


int t;
int n;
int k;
int len[NMAX + 5];
int dp[NMAX + 5][NMAX + 5][2][2];
int tmp_dp[NMAX + 5][2][2];
int tmp_len;
int c[NMAX + 5];
vector<int> graph[NMAX + 5];

void dfs(int nod,int tata){
//  printf("enter %d\n",nod);
  len[nod] = 1;
  dp[nod][0][0][0] = 0;
  dp[nod][0][1][1] = 0;
  dp[nod][1][0][1] = 0;
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it,nod);
    
    tmp_len = min(k,len[nod] + len[it] + 1);
    for(int i = 0;i <= tmp_len;i++){
      for(int j = 0;j < 2;j++){
        for(int k = 0;k < 2;k++){
          tmp_dp[i][j][k] = -inf;
        }
      }
    }

    ///the node should decide if it wants to end the current path going down from node
    ///so dp[nod][j][1][1] should update dp[nod][j + 1][0][1]
    ///also, at the end, add the cost for the current node

    for(int j = 0;j <= len[nod];j++){
      for(int k = 0;k < 2;k++){
        for(int l = 0;l < 2;l++){
          for(int jp = 0;jp <= len[it] && j + jp <= tmp_len;jp++){
            for(int kp = 0;kp < 2;kp++){
              for(int lp = 0;lp < 2;lp++){
                int target_j = j + jp + (k + kp >= 2);
                int target_k = (k ^ kp);
                int target_l = (l | (target_k >= 1));
                //printf("debugu mare %d %d %d %d %d\n",nod,j,k,l,dp[nod][j][k][l]);
                //printf("with        %d %d %d %d %d\n",it,jp,kp,lp,dp[it][jp][kp][lp]);
                //printf("goes in     %d %d %d    %d\n",target_j,target_k,target_l,dp[nod][j][k][l] + dp[it][jp][kp][lp]);
                tmp_dp[target_j][target_k][target_l] = max(tmp_dp[target_j][target_k][target_l],dp[nod][j][k][l] + dp[it][jp][kp][lp]);
              }
            }
          }
        }
      }
    }

    len[nod] = tmp_len;
    for(int j = 0;j <= len[nod];j++){
      for(int k = 0;k < 2;k++){
        for(int l = 0;l < 2;l++){
          dp[nod][j][k][l] = tmp_dp[j][k][l];
        }
      }
    }
  }
  for(int j = 0;j <= len[nod];j++){
    dp[nod][j + 1][0][1] = max(dp[nod][j + 1][0][1],dp[nod][j][1][1]);
  }
  if(len[nod] <= k){
    len[nod]++;
  }
  for(int j = 0;j <= len[nod];j++){
    dp[nod][j][0][1] += c[nod];
    dp[nod][j][1][1] += c[nod];
  }
//  printf("leave %d\n",nod);
}

int main(){

  scanf("%d",&t);

  for(int h = 1;h <= t;h++){
    scanf("%d",&n);
    scanf("%d",&k);

    for(int i = 1;i <= n;i++){
      graph[i].clear();
      len[i]= 0;
      for(int j = 0;j <= k + 1;j++){
        for(int k = 0;k < 2;k++){
          for(int l = 0;l < 2;l++){
            dp[i][j][k][l] = -inf;
            tmp_dp[i][k][l] = -inf;
          }
        }
      }
    }

    for(int i = 1;i <= n;i++){
      scanf("%d",&c[i]);
    }

    for(int i = 1;i < n;i++){
      int u,v;
      scanf("%d %d",&u,&v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    if(k == 0){
      printf("Case #%d: %d\n",h,c[1]);
      continue;
    }

    c[1] += 1e9;

    dfs(1,0);
    int ans = -inf;
    for(int i = 0;i <= k;i++){
      ans = max(ans,dp[1][i][0][1]);
      ans = max(ans,dp[1][i][0][0]);
    }
    ans -= 1e9;
    printf("Case #%d: %d\n",h,ans);
  }

  return 0;
}
