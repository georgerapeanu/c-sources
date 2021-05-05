#include <cstdio>

using namespace std;

FILE *f = fopen("xorfibo.in","r");
FILE *g = fopen("xorfibo.out","w");

const int KMAX = 20;
const int MOD = (1 << KMAX) - 1;
const int PISANO_PERIOD = (1 << KMAX) * 3 / 2;

int total_xor;
int fibb[PISANO_PERIOD];

int get_fibonacci_xor(long long x) {
    int ans = 0;
    if((x / PISANO_PERIOD) % 2 == 1) {
        ans ^= total_xor;
    }
    x %= PISANO_PERIOD;
    ans ^= fibb[x];
    return ans;
}

int main() {

    fibb[0] = 0;
    fibb[1] = 1;
    total_xor = 1;

    for(int i = 2; i < PISANO_PERIOD; i++) {
        fibb[i] = ((fibb[i - 2] + fibb[i - 1]) & MOD);
        total_xor ^= fibb[i];
    }

    for(int i = 1; i < PISANO_PERIOD; i++) {
        fibb[i] ^= fibb[i - 1];
    }
    

    int q;
    fscanf(f,"%d",&q);

    while(q--) {
        int k;
        long long l;
        long long r;

        fscanf(f,"%d %lld %lld",&k,&l,&r);

        fprintf(g,"%d\n",((get_fibonacci_xor(r) ^ (l == 0 ? 0:get_fibonacci_xor(l - 1))) & ((1 << k) - 1)));
    }

    fclose(f);
    fclose(g);

    return 0;
}
