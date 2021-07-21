#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int VMAX = 1e6;

int n;
int v[NMAX + 5];
int fr[VMAX + 5];
long long ways[VMAX + 5];

int main(){
  
  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&v[i]);
    fr[v[i]]++;
  }

  for(int x = 1;x <= VMAX;x++){
    for(int z = x;z <= VMAX;z += x){
      int y = z / x;
      if(x < y && z != x && z != y){
        ways[z] += 1LL * fr[x] * fr[y];
      }
    }
  }

  long long ans = 0;

  for(int i = 1;i <= n;i++){
    ans += ways[v[i]];
  }

  printf("%lld\n",ans);

  return 0;
}
