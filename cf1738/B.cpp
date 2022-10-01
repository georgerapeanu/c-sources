#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  
  scanf("%d", &t);

  while(t--){
     int n, k;
     scanf("%d %d", &n, &k);

     vector<int> s(k, 0);

     for(auto &it:s){
      scanf("%d", &it);
     }

    bool ok = true;

     for(int i = 1;i + 1 < k;i++){
       if(s[i + 1] - s[i] < s[i] - s[i - 1]){
        ok = false;
       }
     }

     if(k > 1){
      if(1LL * (s[1] - s[0]) * (n - k + 1) < s[0]){
        ok = false;
      }
     }

     printf(ok ? "YES\n":"NO\n");
  }

  return 0;
}
