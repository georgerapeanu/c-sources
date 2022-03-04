#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  
  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d",&n);
    
    vector<int> v(n, 0);
    vector<int> pref_max(n, 0);

    for(auto &it:v){
      scanf("%d",&it);
    }
    pref_max[0] = v[0];
    for(int i = 1;i < n;i++){
      pref_max[i] = max(pref_max[i - 1], v[i]);
    }
    int __min = v[n - 1];
    bool ok = false;
    for(int i = n - 2;i >= 0;i--){
      if(__min < pref_max[i]){
        ok = true;
      }
      __min = min(__min, v[i]);
    }

    printf(ok ? "YES\n":"NO\n");
  }

  return 0;
}
