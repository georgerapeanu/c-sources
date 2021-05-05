#include <cstdio>

using namespace std;

FILE *f = fopen("xorfibo.in","r");
FILE *g = fopen("xorfibo.out","w");

const int KMAX = 20;
const int MOD = (1 << KMAX) - 1;
const int RMAX = 1e6;

int fibb[RMAX + 5];

int main() {

    fibb[0] = 0;
    fibb[1] = 1;

    for(int i = 2; i <= RMAX; i++) {
        fibb[i] = ((fibb[i - 2] + fibb[i - 1]) & MOD);
    }

    for(int i = 1; i <= RMAX; i++) {
        fibb[i] ^= fibb[i - 1];
    }

    int q;

    fscanf(f,"%d",&q);

    while(q--) {
        int k;
        long long l,r;
        
        fscanf(f,"%d %lld %lld",&k,&l,&r);

        fprintf(g,"%d\n",((fibb[r] ^ (l == 0 ? 0 : fibb[l - 1])) & ((1 << k) - 1)));
    }

    fclose(f);
    fclose(g);

    return 0;
}
