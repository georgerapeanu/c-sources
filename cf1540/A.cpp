#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int v[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
      scanf("%d",&n);

      for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
      }

      sort(v + 1,v + 1 + n);


      long long ans = v[n] - v[1];
      long long sum = 0;


      for(int i = 1;i <= n;i++){
        ans += sum - 1LL * v[i] * (i - 1);
        sum += v[i];
      }

      cout << ans << "\n";
    }

    return 0;
}
