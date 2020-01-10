#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n,m;
int a[NMAX + 5];
int b[NMAX + 5];
int pos[NMAX + 5];

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d",&n,&m);
        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
            pos[a[i]] = i;
        }
        for(int i = 1; i <= m; i++) {
            scanf("%d",&b[i]);
        }

        int lst = 0;

        long long ans = 0;

        for(int i = 1; i <= m; i++) {
            if(lst < pos[b[i]]) {
                ans += 2 * (pos[b[i]] - (i - 1)) - 1;
                lst = pos[b[i]];
            }
            else {
                ans++;
            }
        }

        printf("%lld\n",ans);

    }

    return 0;
}
