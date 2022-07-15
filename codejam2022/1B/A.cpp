#include <bits/stdc++.h>

using namespace std;

int main(){
  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    int n;
    scanf("%d", &n);
    vector<int> d(n);
    for(auto &it:d){
      scanf("%d", &it);
    }

    vector<int> l_value(n, 0);
    vector<int> r_value(n, 0);

    int best = -1;

    for(int i = 0;i < n;i++){
      l_value[i] = (i == 0 ? 1:l_value[i - 1] + (d[i] >= best));
      best = max(best, d[i]);
    }
    
    best = -1;
    for(int i = n - 1;i >= 0;i--){
      r_value[i] = (i == n - 1 ? 1:r_value[i + 1] + (d[i] >= best));
      best = max(best, d[i]);
    }
    
    int ans = 0;

    for(int i = 0;i <= n;i++){
      ans = max(ans, (i == 0 ? 0:l_value[i - 1]) + (i == n ? 0:r_value[i]));
    }
    printf("Case #%d: %d\n", test, ans);
  }
  return 0;
}
