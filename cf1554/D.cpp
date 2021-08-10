#include <bits/stdc++.h>

using namespace std;

int t;
int n;

int main(){

    scanf("%d",&t);

    while(t--){
      scanf("%d",&n);
      if(n <= 26){
        for(int i = 1;i <= n;i++){
          printf("%c",'a' + i - 1);
        }
      }else{
        int x = (n - 2) / 2;
        for(int i = 1;i <= x;i++){
          printf("a");
        }
        for(int i = 1;i <= n - x - x - 1;i++){
          printf("%c",'a' + i);
        }
        for(int i = 1;i <= x + 1;i++){
          printf("a");
        }
      }
      printf("\n");
    }

    return 0;
}
