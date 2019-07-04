#include <cstdio>
#include <random>

using namespace std;

const int NMAX = 50;
const int VMAX = 1e5;

FILE *g = fopen("overpower.in","w");

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;

    fprintf(g,"%d\n",n);

    for(int i = 1; i <= n; i++) {
        int x,y;

        x = gen() % VMAX + 1;
        y = gen() % VMAX + 1;

        if(x > y) {
            swap(x,y);
        }

        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
