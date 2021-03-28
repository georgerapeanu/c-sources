#include <bits/stdc++.h>

using namespace std;

int t;
int n,u,d,l,r;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d %d %d %d",&n,&u,&r,&d,&l);

        bool ok = false;

        for(int conf = 0;conf < (1 << 4);conf++){
            int _u = u - __builtin_popcount(conf & 3);
            int _r = r - __builtin_popcount(conf & 6);
            int _d = d - __builtin_popcount(conf & 12);
            int _l = l - __builtin_popcount(conf & 9);

            int _min = min(min(_u,_d),min(_l,_r));
            int _max = max(max(_u,_d),max(_l,_r));

            if(0 <= _min && _max <= n - 2){
                ok = true;
                break;
            }
        }

        printf(ok ? "YES\n" : "NO\n");
    }

    return 0;
}
