#include <cstdio>
#include <random>
#include <cassert>

using namespace std;

const int NMAX = 5;
const int MMAX = 5;
const int XMAX = 10;
const int DELTA = 1;

FILE *g = fopen("obstacole.in","w");

int main() {

    random_device rd;
    mt19937_64 gen(rd());

    int n = gen() % NMAX + 1;
    int m = gen() % NMAX + 1;

    fprintf(g,"%d %d\n",n,m);

    for(int i = 1; i <= n; i++) {
        int x,y,xx,yy;
        x = gen() % XMAX + 1;
        y = gen() % XMAX + 1;
        xx = gen() % (XMAX + DELTA - 1) + 1;
        yy = gen() % (XMAX + DELTA - 1) + 1;
        if(xx >= x) {
            xx++;
        }
        if(yy >= y) {
            yy++;
        }
        assert(x != xx);
        assert(y != yy);
        assert(1 <= x && x <= XMAX + DELTA);
        assert(1 <= y && y <= XMAX + DELTA);
        assert(1 <= xx && xx <= XMAX + DELTA);
        assert(1 <= yy && yy <= XMAX + DELTA);
        fprintf(g,"%d %d %d %d\n",x,y,xx,yy);
    }

    for(int i = 1; i <= m; i++) {
        int x = gen() % XMAX + 1;
        int y = gen() % XMAX + 1;
        assert(1 <= x && x <= XMAX + DELTA);
        assert(1 <= y && y <= XMAX + DELTA);
        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
