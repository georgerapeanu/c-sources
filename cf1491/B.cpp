#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100;

int t;
int n,u,v;
int a[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d %d",&n,&u,&v);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }

        int ans = 2 * v;

        for(int i = 1;i < n;i++){
            if(abs(a[i] - a[i + 1]) > 1){
                ans = min(ans,0);
            }else if(abs(a[i] - a[i + 1]) == 1){
                ans = min(ans,u);
                ans = min(ans,v);
            }else{
                ans = min(ans,u + v);
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
