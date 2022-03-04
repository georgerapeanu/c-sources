#include <bits/stdc++.h>

using namespace std;

int main(){
  int t;

  scanf("%d", &t);
  
  while(t--){
    long long hc, dc;
    long long hm, dm;
    long long k, w, a;

    scanf("%lld %lld", &hc, &dc);
    scanf("%lld %lld", &hm, &dm);
    scanf("%lld %lld %lld", &k, &w, &a);

    bool ok = false;
    for(int i = 0;i <= k;i++){
      long long turn_c = ((hc + 1LL * a * (k - i) + dm - 1) / dm);
      long long turn_m = ((hm + dc + 1LL * w * i - 1) / (dc + 1LL * w * i));
      if(turn_c >= turn_m){
        ok = true;
        break;
      }
    }

    printf(ok ? "YES\n":"NO\n");
  }
  return 0;
}
