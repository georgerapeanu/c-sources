#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
const int RMAX = 1e3;

int dist[NMAX + 1][RMAX + 1];

int m,n,g,r;
int d[NMAX + 5];

int main(){

  scanf("%d %d",&m,&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&d[i]);
  }

  scanf("%d %d",&g,&r);

  dist[1][0] = 1;
  deque<pair<int,int> > q;

  q.push_back({1,0});

  while(q.empty() == false){
    int x = q.front().first;
    int y = q.front().second;
    q.pop_front();

    if(x > 1){
      if(y + d[x] - d[x - 1] <= g){
        if(dist[x - 1][y + d[x] - d[x - 1]] == 0){
          dist[x - 1][y + d[x] - d[x - 1]] = dist[x][y];
          q.push_front({x - 1,y + d[x] - d[x - 1]});
        }
      }else if(y == g){
        if(dist[x - 1][0] == 0){
          dist[x][0] = dist[x][y] + 1;
          q.push_back({x,0});
        }
      }
    }
    if(x < n){
      if(y + d[x + 1] - d[x] <= g){
        if(dist[x + 1][y + d[x + 1] - d[x]] == 0){
          dist[x + 1][y + d[x + 1] - d[x]] = dist[x][y];
          q.push_front({x + 1,y + d[x + 1] - d[x]});
        }
      }else if(y == g){
        if(dist[x][0] == 0){
          dist[x][0] = dist[x][y] + 1;
          q.push_back({x,0});
        }
      }
    }
  }

  long long ans = 1e18;

  for(int i = 0;i <= g;i++){
    if(dist[n][i] != 0){
      ans = min(ans,1LL * (g + r) * (dist[n][i] - 1) + i);
    }
  }

  printf("%lld\n",(ans == 1e18 ? -1:ans));

  return 0;
}
