#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int c[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&c[i]);
        }

        int x = n - 1;
        int y = n - 1;
        int best_y = c[1];
        int best_x = c[2];
        long long cost = c[1] + c[2];
        long long ans = 1e18;

        for(int i = 2;i <= n;i++){
            ans = min(ans,cost + 1LL * best_x * x + 1LL * best_y * y);
            if(i % 2 == 0){
                best_y = min(best_y,c[i + 1]);
                y--;
            }else{
                best_x = min(best_x,c[i + 1]);
                x--;
            }
            cost += c[i + 1];
        }
        printf("%lld\n",ans);
    }


    return 0;
}
