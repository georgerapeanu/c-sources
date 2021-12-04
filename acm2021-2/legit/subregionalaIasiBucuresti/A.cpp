#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25;
const int MOD = 1e9 + 7;
const int inv2 = MOD / 2 + 1;

int n;
int dp[1 << NMAX];
int v[NMAX];

vector<int> available;

bool ok[NMAX][NMAX][NMAX];

int gcd(int a,int b){
  if(b == 0){
    return a;
  }
  return gcd(b,a % b);
}

long long lcm(int a,int b){
  return 1LL * a * b / gcd(a,b);
}

int main(){

  scanf("%d",&n);

  for(int i = 0;i < n;i++){
    scanf("%d",&v[i]);
  }

  sort(v,v + n);

  for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
      for(int k = 0;k < n;k++){
        ok[i][j][k] = (lcm(v[i],v[j]) == v[k]);
      }
    }
  }

  dp[1 << (n - 1)] = 1;

  for(int i = n - 1;i >= 0;i--){
    int lft = (1 << (n)) - (1 << (i));
    int rgt = (1 << (n)) - 1;
    available.clear();
    for(int conf = rgt;conf >= lft;conf--){
      if(dp[conf] != 0){
        int cntEgaleRamase = 0;
        for(int it = 0;it <= i;it++){
          cntEgaleRamase += (v[it] == v[i]);
        }
        dp[conf] = 1LL * dp[conf] * cntEgaleRamase % MOD;
        for(int j = 0;j < (int)available.size();j++){
          if(j > 0 && v[available[j]] == v[available[j - 1]]){
            continue;
          }
          int fst = available[j];
          for(int k = j + 1;k < (int)available.size();k++){
            int snd = available[k];
            if(k > j + 1 && v[available[k]] == v[available[k - 1]]){
              continue;
            }
            if(ok[fst][snd][i]){ 
              int target = (conf | (1 << fst) | (1 << snd));
         //     printf("from %d with conf %d,value %d to %d with %d %d\n",i,conf,dp[conf],target,fst,snd);
              if(v[fst] != v[snd]){
                dp[target] += dp[conf];
                if(dp[target] >= MOD){
                  dp[target] -= MOD;
                }
              }else{
                dp[target] = (dp[target] + 1LL * dp[conf] * inv2) % MOD;
              }
          //    printf("target is %d\n",dp[target]);
            }
          }
        }
      }
      for(int h = 0;;h++){
        if((conf >> h) & 1){
          available.push_back(h);
          break;
        }else{
          available.pop_back();
        }
      }
    }
  }
  int ans = dp[(1 << n) - 1];
  int len = 0;


  printf("%d\n",ans);

  return 0;
}
