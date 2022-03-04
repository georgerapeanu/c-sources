#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int n, k;
  scanf("%d %d", &n, &k);

  vector<int> v(n, 0);

  sort(v.begin(), v.end());

  for(auto &it:v){
    scanf("%d", &it);
  }
  vector<int> stuff;
  for(int i = 1;i < n;i++){
    stuff.push_back(v[i] - v[i - 1] - 1);
  }

  int ans = v.back() - v[0] + 1;
  sort(stuff.begin(), stuff.end());
  reverse(stuff.begin(), stuff.end());

  for(int i = 0;i < k - 1;i++){
    ans -= max(0, stuff[i]);
  }

  printf("%d", ans);

  return 0;
}

