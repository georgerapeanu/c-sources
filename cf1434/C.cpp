#include <bits/stdc++.h>

using namespace std;

int t;

void solve(){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);

    if(a - 1LL * b * c > 0){
        printf("-1\n");
        return ;
    }

    /*
     t=kd<c 0-indexed
     a-kdb > 0

     */

    int k = (a - 1) / (1LL * d * b);

    printf("%lld\n",1LL * (k + 1) * a - 1LL * b * d * (1LL * k * (k + 1) / 2));
}

int main(){

    scanf("%d",&t);

    while(t--){
        solve();
    }

    return 0;
}
