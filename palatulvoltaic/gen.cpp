#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;

FILE *g = fopen("palatulvoltaic.in","w");

const int NMAX = 1e3;
const int KMAX = 1e9;

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int k = gen() % NMAX + 1;

    fprintf(g,"%d %d\n",n,k);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % KMAX + 1));
    }

    fprintf(g,"\n");

    for(int i = 2; i <= n; i++) {
        int u = i;
        int v = gen() % (i - 1) + 1;
        fprintf(g,"%d %d\n",u,v);
    }

    fclose(g);

    return 0;
}
