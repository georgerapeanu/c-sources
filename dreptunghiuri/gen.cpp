#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;

FILE *g = fopen("dreptunghiuri.in","w");

const int NMAX = 50;

int main(){

    random_device rd;
    mt19937 gen(rd());

    fprintf(g,"%d %d\n",(int)gen() % NMAX + 1,(int)gen() % NMAX + 1);

    fclose(g);

    return 0;
}
