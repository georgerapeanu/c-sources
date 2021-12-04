#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25;
const int HMAX = 16 * 12;
const int inf = 1e9;

int tests;

int n,h;
int dp[NMAX + 1][HMAX + 1][HMAX + 1];
int ant[NMAX + 1][HMAX + 1][HMAX + 1];
int f[NMAX + 5];
int d[NMAX + 5];
int t[NMAX + 5];
int _times[NMAX + 5];

int main(){

  scanf("%d",&tests);

  for(int test = 1;test <= tests;test++){
    scanf("%d %d",&n,&h);
    h *= 12;
    
    for(int i = 1;i <= n;i++){
      scanf("%d",&f[i]);
    }
    for(int i = 1;i <= n;i++){
      scanf("%d",&d[i]);
    }
    for(int i = 1;i < n;i++){
      scanf("%d",&t[i]);
    }

    for(int i = 1;i <= n;i++){
      for(int j = 0;j <= h;j++){
        for(int k = 0;k <= h;k++){
          dp[i][j][k] = 0;
          ant[i][j][k] = 0;
        }
      }
    }

    for(int i = 1;i <= n;i++){
      _times[i] = 0;
    }

    for(int i = n;i;i--){
      for(int j = h;j >= 0;j--){
        for(int k = j;k >= 0;k--){
          int cnt_fish = max(0,f[i] - d[i] * k);
          if(j < h){
            if(dp[i][j + 1][k + 1] + cnt_fish >= dp[i][j][k]){
              ant[i][j][k] = -1;
              dp[i][j][k] = dp[i][j + 1][k + 1] + cnt_fish;
            }
          }
          if(i < n && j + t[i] <= h){
            if(dp[i + 1][j + t[i]][0] > dp[i][j][k]){
              ant[i][j][k] = -2;
              dp[i][j][k] = dp[i + 1][j + t[i]][0];
            }
          }
        }
      }

    }
    
    int x,y,z;
    
    x = 1;
    y = z = 0;
    

    while(ant[x][y][z] != 0 && x <= n && y <= h && z <= h){
      if(ant[x][y][z] == -1){
        _times[x] += 5;
        y++;
        z++;
      }else{
        z = 0;
        y += t[x];
        x++;
      }
    }

    printf("Case %d:\n",test);
    for(int i = 1;i <= n;i++){
      printf("%d",_times[i]);
      if(i < n){
        printf(", ");
       }
    }
    printf("\n");
    printf("Number of fish expected: %d\n",dp[1][0][0]);
  }

  return 0;
}
