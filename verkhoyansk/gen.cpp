#include <bits/stdc++.h>

using namespace std;

FILE *g = fopen("verkhoyansk.in","w");

const int NMAX = 5e3;
const int QMAX = 1e4;

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int q = gen() % QMAX + 1;

    fprintf(g,"%d %d\n",n,q);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % n + 1));
    }

    while(q--) {
        int x = gen() % n;
        int y = gen() % n;
        if(x > y) {
            swap(x,y);
        }
        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
