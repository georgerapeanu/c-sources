#include <bits/stdc++.h>

using namespace std;

int n,k;
bool available[100005];

int main(){

    int t;

    scanf("%d",&t);

    while(t--){

        scanf("%d %d",&n,&k);


        for(int i = 1;i < k - (n - k);i++){
            printf("%d ",i);
        }

        for(int i = k - (n - k);i <= k;i++){
            printf("%d ",k - (i - (k - (n - k))));
        }

        printf("\n");

    }

    return 0;
}
