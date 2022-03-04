#include <bits/stdc++.h>

using namespace std;

int main(){
    
    int t;

    scanf("%d", &t);

    while(t--){
      int n;
      scanf("%d", &n);
      vector<int> v(n, 0);

      for(auto &it:v){
        scanf("%d", &it);
      }

      int ans = 0;
      for(int i = 0;i < n;i++){
        int cnt = 0;
        for(int j = i;j < n;j++){
          cnt += (v[j] == 0);
          ans += (j - i + 1 + cnt);
        }
      }
      printf("%d\n", ans);
    }

    return 0;
}
