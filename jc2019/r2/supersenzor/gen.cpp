#include <cstdio>
#include <random>

using namespace std;

FILE *g = fopen("supersenzor.in","w");

const int NMAX = 50;
const int VMAX = 1e7;

int main() {
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int t = gen() % VMAX + 1;

    fprintf(g,"%d %d\n",n,t);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % VMAX + 1));
    }

    fclose(g);

    return 0;
}
