#include <bits/stdc++.h>

using namespace std;

const int NMAX = 4e6;

int n,m;
int dp[NMAX + 5];
vector<int> events[NMAX + 5];

int add(int a,int b){
  a += b;
  if(a >= m){
    a -= m;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += m;
  }
  return a;
}

int main(){

  scanf("%d %d",&n,&m);

  for(int x = 2;x <= n;x++){
      for(int j = x,k = 1;j <= n;j += x,k ++){
        events[j].push_back(k);
      }
  }

  int eventSum = 0;
  int sum = 0;

  sum = dp[1] = 1;

  for(int i = 2;i <= n;i++){
    for(auto it:events[i]){
      eventSum = add(eventSum,scad(dp[it],dp[it - 1]));
    }

    dp[i] = add(sum,eventSum);
    sum = add(sum,dp[i]);
  }

  printf("%d\n",dp[n]);

    return 0;
}
