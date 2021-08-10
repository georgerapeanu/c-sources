#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;

int main(){

    scanf("%d",&t);

    while(t--){
      scanf("%d %d",&n,&m);
      m++;
      int ans = 0;
      for(int i = 30;i >= 0;i--){
        if((m >> i) & 1){
          ans |= ((!((n >> i) & 1)) << i);
        }else if((n >> i) & 1){
          break;
        }
      }
      printf("%d\n",ans);
    }

    return 0;
}
