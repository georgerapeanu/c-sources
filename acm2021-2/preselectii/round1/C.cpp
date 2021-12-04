#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
pair<int,int> reducedCave[NMAX + 5];
int dp[NMAX + 5];

int main(){
    
    scanf("%d",&t);
    while(t--){
      scanf("%d",&n);

      for(int i = 1;i <= n;i++){
        int k;
        scanf("%d",&k);
        reducedCave[i].second = k;
        reducedCave[i].first = 0;
        for(int j = 0;j < k;j++){
          int power;
          scanf("%d",&power);
          reducedCave[i].first = max(reducedCave[i].first,power - j + 1);
        }
      }
  
      sort(reducedCave + 1,reducedCave + 1 + n);
      dp[n] = reducedCave[n].first;
      for(int i = n - 1;i >= 1;i--){
        dp[i] = max(reducedCave[i].first,dp[i + 1] - reducedCave[i].second);
      }
    
      printf("%d\n",dp[1]);
    }
    return 0;
}
