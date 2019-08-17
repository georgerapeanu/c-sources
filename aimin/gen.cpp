#include <cstdio>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

FILE *g = fopen("aimin.in","w");

const int NMAX = 1e3;
const int LMAX = 1e8;

int main(){

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    
    fprintf(g,"%d\n",n);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",int(gen() % LMAX + 1));
    }

    fclose(g);

    return 0;
}
