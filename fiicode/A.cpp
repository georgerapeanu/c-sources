#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n,l,r;
int v[NMAX + 5];

int main(){

    scanf("%d %d %d",&n,&l,&r);

    for(int i = 1;i <= n;i++){
      scanf("%d",&v[i]);
    }

    for(int i = 1;i <= n;i++){
      v[n + 1] ^= v[i];
    }
    n++;

    if(r - l + 1 >= n){
      l = 1;
      r = n;
    }

    l = (l - 1) % n + 1;
    r = (r - 1) % n + 1;

    int ans = 0;

    if(l <= r){
      for(int i = l;i <= r;i++){
        ans = max(ans,v[i]);
      }
    }else{
      for(int i = l;i <= n;i++){
        ans = max(ans,v[i]);
      }

      for(int i = 1;i <= r;i++){
        ans = max(ans,v[i]);
      }
    }

    printf("%d\n",ans);

    return 0;
}
