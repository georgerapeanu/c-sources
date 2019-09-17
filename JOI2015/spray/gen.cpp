#include <cstdio>
#include <algorithm>
#include <random>

using namespace std;

const int NMAX = 20;
const int QMAX = 20;
const int KMAX = 10;
const int VMAX = 100;

int main() {
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int q = gen() % QMAX + 1;
    int k = gen() % KMAX + 1;

    printf("%d %d %d\n",n,q,k);

    for(int i = 1; i <= n; i++) {
        printf("%d ",int(gen() % VMAX + 1));
    }
    printf("\n");

    while(q--) {
        int t = gen() % 3 + 1;
        int a = gen() % n + 1;
        int b = gen() % n + 1;
        if(t != 1) {
            if(a > b)swap(a,b);
            printf("%d %d %d\n",t,a,b);
        }
        else {
            b = gen() % VMAX + 1;
            printf("%d %d %d\n",t,a,b);
        }
    }

    return 0;
}
