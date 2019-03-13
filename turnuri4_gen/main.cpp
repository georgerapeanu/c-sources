#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

FILE *g = fopen("turnuri4.in","w");

const int NMAX = 1e4;

int v[NMAX + 5];

int main(){
    srand(time(NULL));

    int n = rand() % NMAX + 1;

    fprintf(g,"%d\n",n);

    for(int i =1;i <= n;i++){
        v[i] = i;
    }

    random_shuffle(v + 1,v + 1 + n);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",v[i]);
    }

    fclose(g);

    return 0;
}
