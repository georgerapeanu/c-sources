#include <cstdio>
#include <ctime>
#include <algorithm>

const int NMAX = 20;
const int VMAX = 50;
const int TMAX = 2000;

int main() {
    srand(time(NULL));
    int n = rand() % NMAX + 1;
    int m = rand() % NMAX + 1;

    printf("%d %d\n",n,m);

    for(int i = 1; i <= n; i++) {
        printf("%d %d %d\n",rand() % VMAX,rand() % TMAX,rand() % (2 * VMAX + 1) - VMAX);
    }

    for(int i = 1; i <= m; i++) {
        printf("%d %d %d\n",rand() % VMAX,rand() % TMAX,rand() % (2 * VMAX + 1) - VMAX);
    }

    return 0;
}
