#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n,k;
int a[NMAX + 5];

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
      scanf("%d",&a[i]);
    }

    long long ans = -1e18;

    for(int i = max(1,n - 2 * k - 5);i <= n;i++){
      for(int j = i + 1;j <= n;j++){
        ans = max(ans,1LL * i * j - 1LL * k * (a[i] | a[j]));
      }
    }
    printf("%lld\n",ans);
  }

  return 0;
}
