#include <bits/stdc++.h>

using namespace std;

const int LGMAX = 16;
const int NMAX = 1e5;
const int VMAX = 1e6;

int n,q;
int v[NMAX + 5];
int fr[VMAX + 5];
int father[LGMAX + 1][NMAX + 5];

int main(){

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&v[i]);
  }

  int l = 0;
  int r = 1;

  for(r = 1;r <= n;r++){
    fr[v[r]]++;
    while(fr[v[r]] > 1){
      l++;
      fr[v[l]]--;
    }

    father[0][r] = l;
  }

  for(int h = 1;h <= LGMAX;h++){
    for(int i = 1;i <= n;i++){
      father[h][i] = father[h - 1][father[h - 1][i]];
    }
  }

  scanf("%d",&q);

  while(q--){
    int l,r;
    scanf("%d %d",&l,&r);

    int ans = 0;

    for(int h = LGMAX;h >= 0;h--){
      if(father[h][r] >= l){
        ans |= (1 << h);
        r = father[h][r];
      }
    }
    ans++;
    printf("%d\n",ans);
  }

  return 0;
}
