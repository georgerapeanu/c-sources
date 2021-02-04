#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int p[NMAX + 5];

int main(){

    int n,k;

    scanf("%d %d",&n,&k);

    if(k == 0){
        printf("-1\n");
    }
    else{
        for(int i = k + 1;i <= n;i++){
            p[i] = i;
        }

        while(k >= 3){
            p[k] = k - 1;
            p[k - 1] = k;
            k -= 2;
        }

        if(k == 2){
            p[2] = 1;
            p[1] = 2;
        }else{
            p[1] = 1;
        }

        for(int i = 1;i <= n;i++){
            printf("%d ",p[i]);
        }
    }

    return 0;
}
