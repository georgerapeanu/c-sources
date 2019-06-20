#include <cstdio>
#include <random>

using namespace std;

const int NMAX = 5e5;
const int MMAX = 5e5;
const int QMAX = 5e5;
const long long VMAX = 1e18;

int main() {

    random_device rd;
    mt19937_64 gen(rd());

    int n = gen() % NMAX + 1;
    int m = gen() % MMAX + 1;
    int q = gen() % QMAX + 1;

    printf("%d %d %d\n",n,m,q);

    for(int i = 1; i <= n; i++) {
        printf("%d ",int(gen() % m) + 1);
    }

    for(int i = 1; i <= q; i++) {
        printf("%lld\n",gen() % (VMAX - n) + n + 1);
    }

    return 0;
}
