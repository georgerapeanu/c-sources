#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

FILE *g = fopen("intersectie.in","w");

const int NMAX = 200;
const int MMAX = 10;
const int TMAX = 10;

int main(){

    srand(time(NULL));

    int nnmax = rand() % NMAX + 1;

    int n = rand() % nnmax + 1;
    int m = rand() % MMAX + 1;
    int t = rand() % TMAX + 1;

    fprintf(g,"%d %d %d\n",n,m,t);

    while(m--){
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        fprintf(g,"%d %d\n",x,y);
    }

    while(t--){
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        fprintf(g,"%d %d\n",x,y);
    }

    fclose(g);

    return 0;
}
