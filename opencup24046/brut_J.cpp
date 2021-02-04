#include <bits/stdc++.h>

using namespace std;

int n,q;
int t,l,r,x;
int a[200005];

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }

    while(q--){
        scanf("%d %d %d %d",&t,&l,&r,&x);

        if(t == 1){
            for(int i = l;i <= r;i++){
                a[i] = max(a[i],x);
            }
        }
        else{
            int xo = x;
            
            for(int i = l;i <= r;i++){
                xo ^= a[i];
            }

            int ans = ((x ^ xo) < x);

            for(int i = l;i <= r;i++){
                ans += ((a[i] ^ xo) < a[i]);
            }

            printf("%d\n",ans);
        }
    }

    return 0;
}
