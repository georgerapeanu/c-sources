#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

FILE *g = fopen("inrudit.in","w");

const int NMAX = 1000;
const int KMAX = 1e7;

int main(){

    srand(time(NULL));

    int nnmax = rand() % NMAX + 1;

    int n = rand() % nnmax + 1;
    int k = rand() % KMAX + 1;

    fprintf(g,"%d\n",k);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%c",'0' + (rand() % 10));
    }

    fclose(g);

    return 0;
}
