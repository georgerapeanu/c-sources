#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

FILE *g = fopen("panza.in","w");

const int PMAX = 1e6;
const int NMAX = 1e5;
const int MMAX = 1e5;
const int VMAX = 1e6;

int main(){

    srand(time(NULL));

    int n = rand() % NMAX + 1;
    int m = rand() % min(PMAX / n,MMAX) + 1;

    if(rand() & 1){
        swap(n,m);
    }

    int st = rand() % m + 1;
    int dr = rand() % m + 1;
    if(st > dr){
        swap(st,dr);
    }

    fprintf(g,"%d %d %d %d\n",n,m,st,dr);

    for(int i = 1;i <= m;i++){
        fprintf(g,"%d ",rand() % VMAX + 1);
    }

    fprintf(g,"\n");

    for(int i = 1;i <= n;i++){
        int st = rand() % m + 1;
        int dr = rand() % m + 1;
        if(st > dr){
            swap(st,dr);
        }
        fprintf(g,"%d %d\n",st,dr);
    }

    fclose(g);

    return 0;
}
