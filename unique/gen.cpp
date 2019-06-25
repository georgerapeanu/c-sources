#include <cstdio>
#include <algorithm>
#include <random>

using namespace std;

FILE *g = fopen("unique.in","w");

const int TMAX = 10;
const int NMAX = 5e3;

int main() {
    random_device rd;
    mt19937 gen(rd());

    int t = gen() % TMAX + 1;

    fprintf(g,"%d\n",t);

    while(t--) {
        int n = gen() % NMAX + 1;
        int VMAX = gen() % n + 1;

        fprintf(g,"%d\n",n);

        for(int i = 1; i <= n; i++) {
            fprintf(g,"%d ",int(gen() % VMAX + 1));
        }
        fprintf(g,"\n");
    }

    fclose(g);

    return 0;
}
