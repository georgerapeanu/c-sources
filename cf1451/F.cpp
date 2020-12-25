#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;
int a[105][105];
int xo[105];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                scanf("%d",&a[i][j]);
                xo[i + j] = 0;
            }
        }

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                xo[i + j] ^= a[i][j];
            }
        }

        bool ok = true;

        for(int i = 1;i <= n + m;i++){
            ok &= (xo[i] == 0);
        }

        if(ok){
            printf("Jeel\n");
        }
        else{
            printf("Ashish\n");
        }
    }

    return 0;
}
