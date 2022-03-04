#include <bits/stdc++.h>

using namespace std;

int main() {

  int n, k1, k2;

  scanf("%d", &n);

  vector<vector<int> > jumps(2, vector<int>());

  scanf("%d",&k1);
  jumps[0] = vector<int>(k1, 0);
  for(auto &it:jumps[0]) {
    scanf("%d", &it);
  }
  
  scanf("%d", &k2);
  jumps[1] = vector<int>(k2, 0);
  for(auto &it:jumps[1]) {
    scanf("%d", &it);
  }

  vector<vector<int> > status(2, vector<int>(n, 0));
  vector<vector<int> > non_loses(2, vector<int>());
  non_loses[0] = vector<int>(n, (int)jumps[0].size()); 
  non_loses[1] = vector<int>(n, (int)jumps[1].size()); 

  status[0][0] = status[1][0] = -1;

  queue<pair<int,int> > q;
  q.push({0, 0});
  q.push({1, 0});

  while(!q.empty()) {
    int player = q.front().first;
    int x = q.front().second;
    q.pop();

    for(auto it:jumps[player ^ 1]) {
      int nxt_x = (x + n - it) % n;
      int nxt_player = player ^ 1;

      if(status[nxt_player][nxt_x] == 0) {
        if(status[player][x] == -1) {
          status[nxt_player][nxt_x] = 1;
          q.push({nxt_player, nxt_x});
        }else {
          non_loses[nxt_player][nxt_x]--;
          if(non_loses[nxt_player][nxt_x] == 0) {
            status[nxt_player][nxt_x] = -1;
            q.push({nxt_player, nxt_x});
          }
        }
      }
    }
  }

  for(int i = 0;i < 2;i++) {
    for(int j = 1;j < n;j++) {
      printf(status[i][j] == 0 ? "Loop ":(status[i][j] == 1 ? "Win ":"Lose "));
    }
    printf("\n");
  }

  return 0;
}
