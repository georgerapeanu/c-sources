#include <bits/stdc++.h>

using namespace std;

int t;
int n;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(i == j || i == j - 1 || (i == n && j == 1)){
                    printf("%d ",1);
                }
                else{
                    printf("%d ",0);
                }
            }
            printf("\n");
        }
    }

    return 0;
}
