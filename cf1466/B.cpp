#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int x[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&x[i]);
        }

        sort(x + 1,x + 1 + n);

        int ans = 0;

        for(int i = 1;i <= n;){
            int l,r;
            l = r = i;

            while(r + 1 <= n && x[r + 1] <= x[r] + 1){
                r++;
            }

            ans += min(r - l + 1,x[r] - x[l] + 2);

            i = r + 1;
        }

        printf("%d\n",ans);
    }

    return 0;
}
