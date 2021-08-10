#include <bits/stdc++.h>

using namespace std;

int n,m,k;
int v[1005];

int main(){

  scanf("%d %d %d",&n,&m,&k);

  for(int i = 1;i <= m + 1;i++){
    scanf("%d",&v[i]);
  }

  int ans = 0;

  for(int i = 1;i <= m;i++){
    ans += (__builtin_popcount(v[i] ^ v[m + 1]) <= k);
  }

  printf("%d\n",ans);

  return 0;
}
