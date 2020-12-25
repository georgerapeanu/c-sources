#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int xo = 0;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        xo = 0;

        for(int i = 1;i <= n;i++){
            xo ^= i;
        }

        long long ans = 0;

        for(int i = 0;i <= 30;i++){
            if((1 << i) > n){
                break;
            }
            if((xo >> i) & 1){
                ans += (1 << i);
            }
            else{
                ans += (2LL << i);
            }
        }

        printf("%lld\n",ans);
    }

    return 0;
}
