#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;
int a[105][105];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                scanf("%d",&a[i][j]);
                if(a[i][j] % 2 != (i + j) % 2){
                    printf("%d ",a[i][j] + 1);
                }
                else{
                    printf("%d ",a[i][j]);
                }
            }
            printf("\n");
        }
    }

    return 0;
}
