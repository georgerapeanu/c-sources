#include <bits/stdc++.h>

using namespace std;

int t;
int c,d,x;
int cnt[20000005];

int main(){

    for(int i = 1;i <= 20000000;i++){
        cnt[i] = 1;
    }

    for(int i = 2;i <= 20000000;i++){
        if(cnt[i] == 1){
            for(int j = i;j <= 20000000;j += i){
                cnt[j] <<= 1;
            }
        }
    }

    scanf("%d",&t);

    while(t--){
        scanf("%d %d %d",&c,&d,&x);
       
        long long ans = 0;

        for(int g = 1;1LL * g * g <= x;g++){
            if(x % g == 0){
                int _x;
                _x = x / g + d;
                if(_x % c == 0){
                    _x /= c;
                    ans += cnt[_x];
                }
                if(x != g * g){
                    _x = g + d;
                    if(_x % c == 0){
                        _x /= c;
                        ans += cnt[_x];
                    }
                }
            }
        }

        printf("%lld\n",ans);
    }

    return 0;
}
