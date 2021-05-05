#include "fiboxor.h"

const int KMAX = 20;
const int MOD = (1 << KMAX) - 1;
const int RMAX = 1e6;

int fibb[RMAX + 5];

void init(int q) {

    fibb[0] = 0;
    fibb[1] = 1;

    for(int i = 2; i <= RMAX; i++) {
        fibb[i] = ((fibb[i - 2] + fibb[i - 1]) & MOD);
    }

    for(int i = 1; i <= RMAX; i++) {
        fibb[i] ^= fibb[i - 1];
    }
}

int query(int k,long long l,long long r) {
    return ((fibb[r] ^ (l == 0 ? 0 : fibb[l - 1])) & ((1 << k) - 1));
}
