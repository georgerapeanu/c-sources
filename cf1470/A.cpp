#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n,m;

int k[NMAX + 5];
int c[NMAX + 5];

int main(){
    
    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            scanf("%d",&k[i]);
        }
        for(int i = 1;i <= m;i++){
            scanf("%d",&c[i]);
        }

        sort(k + 1,k + 1 + n,greater<int>());

        long long ans = 0;

        for(int i = 1;i <= n;i++){
            ans += c[min(k[i],i)];
        }

        printf("%lld\n",ans);
    }

    return 0;
}
