#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n;
int where[NMAX + 5];
int v[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        int ans = 0;
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
        }

        for(int i = n;i;i--){
            where[i] = (i + v[i] > n ? i + v[i]:where[i + v[i]]);
            ans = max(ans,where[i] - i);
        }

        printf("%d\n",ans);
    }

    return 0;
}
