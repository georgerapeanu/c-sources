#include <cassert>
#include "coolrot.h"

const int MAX_N = 100000;

// The upper bound of m
// I sure hope this one is ok
const int MAX_D = 400;

// global n
int _n;

// Binary indexed tree code
int aib[1+MAX_N];

static inline int lsb(int x) {
    return x & (-x);
}

void update_aib(int pos, int val) {
    while(pos <= MAX_N) {
        aib[pos] += val;
        pos += lsb(pos);
    }
}

int query_aib(int pos) {
    int res = 0;
    while(pos > 0) {
        res = res + aib[pos];
        pos -= lsb(pos);
    }
    return res;
}

// nr_inv[i] = the number of inversions if we rotate the array
//             by i positions
long long nr_inv[MAX_N];

// best[i] = the best number of rotations divisible by i
int best[1+MAX_N];

void init(int n, const int a[], int q) {
    _n = n;
    
    // Calculate the number of inversions in the original array
    for(int i = 0; i < n; ++i) {
        // We want to see how many elements greater than a[i] are there in
        // the prefix of size i - 1
        
        // To do that, we use a BIT. To do that, we mark element a[i] and see how many
        // elements from a[i] + 1...n - 1 are already marked
        
        // Since BIT doesn't work with suffix sums (it does, but it's inefficient)
        // we will transform the element a[i] into n - a[i], so that we will have to
        // do a prefix sum (in a way, reverse the elements

        // Because of this transformation, the elements will be in range 1..n,
        // so the BIT will work (BIT goes into an infinit loop if you update the position 0)

        nr_inv[0] = nr_inv[0] + query_aib(n - a[i]);
        update_aib(n - a[i], 1);
    }

    // We move the first element to the end and see how the number
    // of inversions changes
    // When we erase the element x from the beginning we lose the inversions with:
    // 0, 1, 2, 3, 4, ..., x - 1 => x elements
    // When we append the element x to the end, we will get the inversions with:
    // x + 1, x + 2, ..., n - 1 => n - x - 1 elements
    for(int i = 0; i < n - 1; ++i)
        nr_inv[i + 1] = nr_inv[i] + (n - a[i] - 1) - a[i];

    // To calculate best, we simply do a brute-force
    // It will have a complexity of O(NlogN)
    for(int d = 1; d < n; ++d)
        for(int i = d; i < n; i += d)
            if(nr_inv[i] < nr_inv[best[d]])
                best[d] = i;
}

// (euclidx[i], euclidy[i]) is a cached euclid solution
int euclidx[400], euclidy[400];

// Solve an equation of type:
// a*x + b*y = gcd(a, b) (modulo mod), where a and b are known
// by doing Euclid's Extended Algorithm
int euclid(int a, int b, int &x, int &y, int mod) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int xp, yp;
        int d = euclid(b, a % b, xp, yp, mod);
        x = yp;
        y = (xp - (long long)a / b * yp % mod + mod) % mod;
        return d;
    }
}

// K = 2
// The optimal number of rotations will be a multiple of gcd(ds[0], ds[1])
// We solve the equation ds[0] * x + ds[1] * y = gcd(ds[0], ds[1])
// and then we multiply this equation with optD / gcd(ds[0], ds[1])
// where optD is the optimal number of rotations
void query(int m,const int ds[]) {
    assert(m == 2);
    int x, y;
    int d = euclid(ds[0], ds[1], x, y, _n);

    x = (long long)x * best[d] / d;
    y = (long long)y * best[d] / d;
    
    if(x != 0)
        update(ds[0], x);
    if(y != 0)
        update(ds[1], y);
}

