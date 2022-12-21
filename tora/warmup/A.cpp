#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++) {
    int n;
    scanf("%d", &n);

    vector<int> v(n, 0);

    int ans = 0;

    for(auto &it:v){
      scanf("%d", &it);
    }

    int __max = 0;

    for(auto &it:v){
      __max = max(__max, it);
    }

    int __min = __max;

    for(auto &it:v){
      __min = min(__min, it);
      ans = max(ans, it - __min);
    }

    printf("SHOW #%d: %d\n", test, ans);
  }
  
  return 0;
} 
