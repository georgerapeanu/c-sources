#include <bits/stdc++.h>

using namespace std;

int n,m;
int c[1005][1005];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d",&c[i][j]);
        }
    }

    long long a = 0;
    long long b = 0;
    long long d = 0;
    long long e = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            a += 16 * c[i][j];
            b += 8LL * c[i][j] * (4LL * i - 2);
            d += 8LL * c[i][j] * (4LL * j - 2);
            e += ((4LL * i - 2) * (4LL * i - 2) + (4LL * j - 2) * (4LL * j - 2)) * c[i][j];
        }
    }

    long long bst = 1e18;
    int j = -1,i = - 1;

    for(int x = 0; x <= n; x++) {
        for(int y = 0; y <= m; y++) {
            long long cst = a * (x * x + y * y) - b * x - d * y + e;
            if(cst < bst) {
                bst = cst;
                i = x;
                j = y;
            }
        }
    }

    printf("%lld\n%d %d\n",bst,i,j);

    return 0;
}
