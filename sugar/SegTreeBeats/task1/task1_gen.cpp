#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

FILE *g = fopen("task1.in","w");

const int NMAX = 1e5;
const int VMAX = 1e9;
const int PMAX = 3e7;

int main() {

    srand(time(NULL));

    int nmax = rand() % NMAX + 1;
    int n = rand() % nmax + 1;
    int q = PMAX / n;

    int vmax = rand() % VMAX + 1;

    fprintf(g,"%d %d\n",n,q);

    for(int i = 1; i <= n; i++) {
        int x = rand() % vmax + 1;
        fprintf(g,"%d ",x);
    }

    fprintf(g,"\n");

    while(q--) {
        int t = rand() % 2 + 1;
        int l = rand() % n + 1;
        int r = rand() % n + 1;

        if(l > r) {
            swap(l,r);
        }

        if(t == 1) {
            int x;
            x = rand() % VMAX + 1;

            fprintf(g,"%d %d %d %d\n",t,l,r,x);
        }
        else {
            fprintf(g,"%d %d %d\n",t,l,r);
        }
    }

    fclose(g);

    return 0;
}
