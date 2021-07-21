#include <bits/stdc++.h>

using namespace std;

int main(){
  
    int t;
    
    scanf("%d",&t);

    while(t--){
      int n,x,t;
      scanf("%d %d %d",&n,&x,&t);
      int k = max(0,n - (t / x));
      long long ans = 0;
      ///1....k -> t/x * k
      ans += 1LL * int(t / x) * k;
      ///k+1..n ->  n - i -> n * (n - k) - (n - k) * (n + k + 1) / 2
      ans += 1LL * n * (n - k);
      ans -= 1LL * (n - k) * (1LL * n + 1LL * k + 1) / 2;
      printf("%lld\n",ans);
    }
  
    return 0;
}
