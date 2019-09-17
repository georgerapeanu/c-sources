#include <bits/stdc++.h>

using namespace std;

const int NMAX = 55;

int n,m;
int a[NMAX + 5][NMAX + 5];
int b[NMAX + 5][NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    int cnt = 0;

    for(int i = 1;i < n;i++){
        for(int j = 1;j < m;j++){
            if(a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1){
                b[i][j] = b[i][j + 1] = b[i + 1][j] = b[i + 1][j + 1] = 1;
                cnt++;
            }
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(a[i][j] != b[i][j]){
                printf("-1\n");
                return 0;
            }
        }
    }
    
    printf("%d\n",cnt);
    for(int i = 1;i < n;i++){
        for(int j = 1;j < m;j++){
            if(a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1){
                printf("%d %d\n",i,j);
            }
        }
    }

    return 0;
}
