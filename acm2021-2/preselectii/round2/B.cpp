#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e2;
const int LGMASK = 12;
const int inf = 1e9;

int n;
int a[NMAX + 5];
int dp[NMAX + 5][1 << LGMASK];
int dist[1 << LGMASK];

int main(){

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&a[i]);
  }

  for(int i = 1;i <= n;i++){
    for(int conf = 0;conf < (1 << LGMASK);conf++){
      dp[i][conf] = -inf;
    }
  }

  int ans = 0;
  dp[1][0] = 0;

  for(int i = 1;i <= n;i++){
    priority_queue<pair<int,int> > pq;
    for(int conf = 0;conf < (1 << LGMASK);conf++){
      dist[conf] = dp[i][conf];
      pq.push({dist[conf],conf});
    }
    while(!pq.empty()){
      pair<int,int> tmp = pq.top();
      pq.pop();
      if(dist[tmp.second] != tmp.first){
        continue;
      }
      int nod = tmp.second;
      for(int mask = 7,fstPos = i - LGMASK + 1;mask < (1 << LGMASK);mask <<= 1,fstPos++){
        if(fstPos <= 0){
          continue;
        }
        if((nod & mask) == 0){
          int to = nod ^ mask;
          int cost = 0;
          for(int h = 0;h < LGMASK;h++){
            if((mask >> h) & 1){
              cost += a[fstPos + h];
            }
          }
          if(dist[to] < dist[nod] + cost){
            dist[to] = dist[nod] + cost;
            pq.push({dist[to],to});
          }
        }else if((nod & mask) == mask){
          int to = nod ^ mask;
          int cost = 0;
          for(int h = 0;h < LGMASK;h++){
            if((mask >> h) & 1){
              cost -= a[fstPos + h];
            }
          }
          if(dist[to] < dist[nod] + cost){
            dist[to] = dist[nod] + cost;
            pq.push({dist[to],to});
          }
        }
      }
      for(int conf = 0;conf < (1 << LGMASK);conf++){
        dp[i][conf] = dist[conf];
      }
    }
    for(int conf = 0;conf < (1 << LGMASK);conf++){
      dp[i + 1][conf >> 1] = max(dp[i + 1][conf >> 1],dp[i][conf]);
      ans = max(ans,dp[i][conf]);
    }
  }

  printf("%d\n",ans);

  return 0;
}
