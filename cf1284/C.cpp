#include <cstdio>

using namespace std;

const int NMAX = 25e4;

int n,m;
int fact[NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = 1LL * i * fact[i - 1] % m;
    }

    int ans = 0;

    for(int l = 1; l <= n; l++) {
        ans = (ans + 1LL * ((1LL * fact[l] * fact[n - l + 1]) % m) * (n - l + 1)) % m;
    }

    printf("%d\n",ans);

    return 0;
}
