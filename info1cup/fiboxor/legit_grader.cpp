#include "fiboxor.h"

const int KMAX = 20;
const int MOD = (1 << KMAX) - 1;
const int PISANO_PERIOD = 3 << 19;
int fibb[PISANO_PERIOD];

int get_fibonacci_xor(long long x) {
    int ans = 0;
    if((x / PISANO_PERIOD) % 2 == 1) {
        ans ^= fibb[PISANO_PERIOD - 1];
    }
    x %= PISANO_PERIOD;
    ans ^= fibb[x];
    return ans;
}

void init(int q) {

    fibb[0] = 0;
    fibb[1] = 1;

    for(int i = 2; i < PISANO_PERIOD; i++) {
        fibb[i] = ((fibb[i - 2] + fibb[i - 1]) & MOD);
    }

    for(int i = 1; i < PISANO_PERIOD; i++) {
        fibb[i] ^= fibb[i - 1];
    }
}

int query(int k,long long l,long long r) {
    return ((get_fibonacci_xor(r) ^ (l == 0 ? 0:get_fibonacci_xor(l - 1))) & ((1 << k) - 1));
}
