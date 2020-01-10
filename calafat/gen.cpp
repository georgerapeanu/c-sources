#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;

FILE *g = fopen("calafat.in","w");

const int NMAX = 1e4;
const int MMAX = 1e4;

int main() {
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int m = gen() % MMAX + 1;

    fprintf(g,"%d %d\n",n,m);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % n + 1));
    }

    fprintf(g,"\n");

    for(int i = 1; i <= m; i++) {
        int l = gen() % n + 1;
        int r = gen() % n + 1;

        if(r < l) {
            swap(l,r);
        }

        fprintf(g,"%d %d\n",l,r);
    }

    fclose(g);

    return 0;
}
