#include <bits/stdc++.h>

using namespace std;

int t;
int n,m,a,b;

int main(){
  
  scanf("%d",&t);

  for(int test = 1;test <= t;test++){

    scanf("%d %d %d %d",&n,&m,&a,&b);

    if(n + m - 1 <= a && n + m - 1 <= b){
      printf("Case #%d: Possible\n",test);
      for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
          if(i == 1 && j == 1){
            printf("%d ",a - (n + m - 2));
          }else if(i == 1 && j == m){
            printf("%d ",b - (n + m - 2));
          }else{
            printf("1 ");
          }
        }
        printf("\n");
      }
    }else{
      printf("Case #%d: Impossible\n",test);
    }

  }

  return 0;
}
