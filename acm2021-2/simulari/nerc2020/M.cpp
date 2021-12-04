#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int k;
vector<int> graph[NMAX + 5];
int dp[NMAX + 5];
int last[NMAX + 5];

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
      cin >> k;
      while(k--){
        int value;
        cin >> value;
        if(last[value] != 0){
          graph[last[value]].push_back(i);
        }
        last[value] = i;
      }
    }

    dp[n] = 1;

    for(int i = n - 1;i;i--){
      dp[i] = 1;
      for(auto it:graph[i]){
        dp[i] = max(dp[i],dp[it] + 1);
      }
    }

    cout << dp[1];
    

    return 0;
}
