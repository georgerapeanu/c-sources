#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

FILE *g = fopen("in","w");

const int NMAX = 1e3;
const int VMAX = 1e9;

int main(){

    srand(time(NULL));

    int n = rand() % NMAX + 1;
    int k = rand() % VMAX + 1;
    int nvmax = rand() % VMAX + 1;

    fprintf(g,"%d %d\n",n,k);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",rand() % nvmax + 1);
    }

    fclose(g);

    return 0;
}
