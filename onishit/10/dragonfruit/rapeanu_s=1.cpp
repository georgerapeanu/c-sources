#include <bits/stdc++.h>

using namespace std;

const int KMAX = 1000;
const int MOD = 1e9 + 7;
const int inf = 1e9;

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}

pair<int, int> fr[KMAX + 5]; ///fr[i] = {the last prefix sum = i mod k, and the last position on which it occurs}

int main(){

  ifstream f("dragonfruit.in");
  ofstream g("dragonfruit.out");

  int t;

  f >> t;

  while(t--){
    int n, k, s;
    f >> n >> k >> s;
    
    assert(s == 1);

    memset(fr, 0, sizeof(fr));

    int sum = 0;
    pair<int, int> ans = {inf, 0};
    for(int i = 1;i <= n;i++){
      int val;
      f >> val;
      sum += val;
      if(sum - fr[sum % k].first == k){
        if(ans.first > i - fr[sum % k].second){
          ans.first = i - fr[sum % k].second;
          ans.second = 1;
        }else if(ans.first == i - fr[sum % k].second){
          ans.second = add(ans.second, 1);
        }
      }
      fr[sum % k] = {sum, i};
    }
    if(ans.first == inf){
      ans = {0, 0};
    }
    g << ans.first << " " << ans.second << "\n";
  }

  f.close();
  g.close();

  return 0;
}
