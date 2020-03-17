#include <cstdio>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

FILE *g = fopen("shoebox.in","w");

const int NMAX = 1e3;
const int LMAX = 1e3;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    fprintf(g,"%d\n",gen() % 2 + 1);

    int n = gen() % NMAX + 1;

    fprintf(g,"%d\n",n);

    for(int i = 1;i <= n;i++){
        int x = gen() % LMAX + 1;
        int y = gen() % LMAX + 1;
        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
