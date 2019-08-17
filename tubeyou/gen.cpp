#include <cstdio>
#include <algorithm>
#include <random>

using namespace std;

const int NMAX = 5e3;
const int KMAX = 1e9;
const int QMAX = 5e3;

FILE *g = fopen("tubeyou.in","w");

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n,k,q;

    n = gen() % NMAX + 1;
    k = gen() % KMAX + 1;
    q = gen() % QMAX + 1;

    fprintf(g,"%d %d %d\n",n,k,q);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % n + 1));
    }
    fprintf(g,"\n");
    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % KMAX + 1));
    }
    fprintf(g,"\n");

    for(int i = 1; i <= q; i++) {
        int t = gen() & 1;

        if(t == 0) {
            int x = gen() % n + 1;
            fprintf(g,"%d %d\n",t,x);
        }
        else {
            int x = gen() % n + 1;
            int y = gen() % n + 1;
            fprintf(g,"%d %d %d\n",t,x,y);
        }
    }

    fclose(g);

    return 0;
}
