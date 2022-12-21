#include <bits/stdc++.h>

using namespace std;

int main(){

  int n, m;
  scanf("%d %d", &n, &m);

  vector<int> v(n, 0);

  for(auto &it:v){
    scanf("%d", &it);  
  }

  sort(v.begin(), v.end());

  int cutSoFar = 0;

  for(int i = n - 1;i >= 0;i--){
    if(i > 0 && cutSoFar + 1LL * (v[i] - v[i - 1]) * (n - i) < m) {
      cutSoFar += (v[i] - v[i - 1]) * (n - i);
    } else {
      //cutSoFar + 1LL * x * (n - i) >= m
      //x * (n - i) >= m - cutSoFar
      //x >= (m - cutSoFar) / (n - i)
      int x = (m - cutSoFar + n - i - 1) / (n - i);
      printf("%d\n", v[i] - x);
      return 0;
    }
  }
  
  assert(false);

  return 0;
}
