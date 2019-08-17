#include <cstdio>
#include <random>
#include <algorithm>
#include <cassert>

using namespace std;

const int NMAX = 1e4;
const int QMAX = 1e4;
const int VMAX = 1e6;

FILE *g = fopen("deletegcd.in","w");

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int q = gen() % QMAX + 1;

    assert(1 <= n && n <= NMAX);
    assert(1 <= q && q <= QMAX);
    fprintf(g,"%d %d\n",n,q);

    int vmax = gen() % VMAX + 1;

    for(int i = 1; i <= n; i++) {
        int x = gen() % vmax + 1;
        assert(1 <= x && x <= vmax);
        fprintf(g,"%d ",x);
    }

    fprintf(g,"\n");

    while(q--) {
        int x = gen() % (n - 1) + 1;
        int y = gen() % (n - x) + x + 1;

        assert(1 <= x && x < y && y <= n);
        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
