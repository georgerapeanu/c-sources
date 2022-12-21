#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;
const int PMAX = 12;
int n;
int value[NMAX + 5];
int p;
int jump[PMAX + 5];
int dp[1 << PMAX][NMAX + 5];

ifstream f("morcovi.in");
ofstream g("morcovi.out");

/*
 * (a << b) ->  a * 2 ^ b
 * 1 << b -> 2 ^ b
 * 101 << 2 -> 10100
 * (a >> b)
 * 10001 >> 2 -> 100
 * a / 2^b
 * &, |, ^
 * 
*/

int main(){

 f >> n;

 for(int i = 1;i <= n;i++){
  f >> value[i];
 }

 f >> p;
 for(int i = 0;i < p;i++){
  f >> jump[i];
 }

 for(int i = 1;i <= n;i++){
  dp[(1 << p) - 1][i] = value[i];
 }

 for(int conf = (1 << p) - 2;conf >= 0;conf--){
  for(int i = 1;i <= n;i++){
    for(int j = 0;j < p;j++){
      if((conf >> j) & 1){
        continue;
      }
      if(i+jump[j] <= n){
        dp[conf][i] = max(dp[conf][i], value[i] + dp[conf | (1 << j)][i + jump[j]]);
      }
      if(i-jump[j] >= 1){
        dp[conf][i] = max(dp[conf][i], value[i] + dp[conf | (1 << j)][i - jump[j]]);
      }
    }
  }
 }

 int answer = 0;

 for(int i = 1;i <= n;i++){
  answer = max(answer, dp[0][i]);
 }

 g << answer;

 f.close();
 g.close();

 return 0;
}
