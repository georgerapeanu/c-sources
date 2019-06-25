#include <cstdio>
#include <algorithm>
#include <random>

using namespace std;

FILE *g = fopen("eq.in","w");

const int NMAX = 5e3;
const int MMAX = 5e3;
const int VMAX = (1 << 24);

int main(){
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int m = gen() % MMAX + 1;

    fprintf(g,"%d %d\n",n,m);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d ",int(gen() % VMAX + 1));
    }

    fprintf(g,"\n");

    for(int i = 1;i <= m;i++){
        int l,r;
        
        l = gen() % n + 1;
        r = gen() % n + 1;

        if(l > r){
            swap(l,r);
        }

        fprintf(g,"%d %d\n",l,r);
    }

    fclose(g);

    return 0;
}
