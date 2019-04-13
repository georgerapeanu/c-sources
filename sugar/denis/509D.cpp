#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int NMAX = 1e2;
const int MMAX = 1e2;

int n,m;
long long v[NMAX + 5][MMAX + 5];
long long a[NMAX + 5];
long long b[MMAX + 5];

long long gcd(long long a,long long b) {
    if(!b) {
        return a;
    }

    return gcd(b,a % b);
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%lld",&v[i][j]);
        }
    }

    for(int j = 1; j <= m; j++) {
        b[j] = -1;
    }

    b[1] = 0;

    for(int i = 1; i <= n; i++) {
        a[i] = v[i][1];
    }

    for(int j = 1; j <= m; j++) {
        b[j] = v[1][j] - a[1];
    }

    long long mod = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            mod = gcd(mod,abs(a[i] + b[j] - v[i][j]));
        }
    }

    if(mod == 0) {
        mod = 1e18;
    }

    for(int j = 1; j <= m; j++) {
        b[j] = (b[j] % mod + mod) % mod;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if((a[i] + b[j]) % mod != v[i][j]) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n%lld\n",mod);

    for(int i = 1; i <= n; i++) {
        printf("%lld ",a[i]);
    }

    printf("\n");

    for(int j = 1; j <= m; j++) {
        printf("%lld ",b[j]);
    }

    printf("\n");

    return 0;
}
