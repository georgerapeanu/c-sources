#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int a[NMAX + 5];

int main(){

    scanf("%d",&t);
    
    while(t--){
      scanf("%d",&n);
      long long ans = 0;
      for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        if(i > 1){
          ans = max(ans,1LL * a[i - 1] * a[i]);
        }
      }
      printf("%lld\n",ans);
    }

    return 0;
}
