#include <cstdio>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

FILE *g = fopen("acgt.in","w");

int NMAX = 1e8;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    fprintf(g,"%d\n",gen() % NMAX + 1);

    fclose(g);

    return 0;
}
