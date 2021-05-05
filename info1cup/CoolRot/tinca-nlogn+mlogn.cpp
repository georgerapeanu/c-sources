#include "coolrot.h"
#include <cstdio>

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
    //fprintf(stderr,"doing init");
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
//    fprintf(stderr,"done init");
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

// Let d = gcd(ds[0], ds[1], ds[2], ..., ds[m - 1])
// Suppose that the optimal number of rotations is D, where D is a multiple of d.
// That means that we have to find a solution to the following equation:
// ds[0] * y[0] + ds[1] * y[1] + ... + ds[m - 1] * y[m - 1] = D

// If m == 1, the solution is obvious: d = ds[0], and
// ds[0] * y[0] = D => y[0] = D / ds[0] (the division is legal, because ds[0] is a divisor of D)

// If m == 2, then we can find the solution to the following equation:
// ds[0] * y[0] + ds[1] * y[1] = gcd(ds[0], ds[1])
// by doing Euclid's Extended Algorithm, then we multiply the equation by
// D / gcd(ds[0], ds[1]), which is legal, and we will have a solution to the original equation

// If m > 2, then we can apply Euclid's algorithm m - 1 times in the following way:
// We do Euclid's Algorithm on the two ds's. Now we know how to write gcd(ds[0], ds[1]).
// We do Euclid's Algorithm on gcd(ds[0], ds[1]) and ds[2]. Now we know
// how to write gcd(ds[0], ds[1], ds[2])
// ...
// We do Euclid's Algorithm on gcd(ds[0], ds[1], ..., ds[m - 2]) and ds[m - 1]
// Now we know how to write gcd(ds[0], ds[1], ds[2], ..., ds[m - 1])
// To find out the original coefficients to the problem, we propagate the intermediate
// solutions. For instance, if we the coefficient of gcd(ds[0], ds[1], ..., ds[t]) is C,
// then we multiply the coefficients of ds[0], ds[1], ..., ds[t] with C.
void query(int m,const int ds[]) {
//    fprintf(stderr,"doing query");
    int n = _n;

    if(m == 1) { // m == 1 case
        int coef = best[ds[0]] / ds[0];
        if(coef != 0)
            update(ds[0], best[ds[0]] / ds[0]);
    } else { // m >= 2 case
        // m == 2 and m > 2 are solved together
        int d = euclid(ds[0], ds[1], euclidx[0], euclidy[0], n);
        for(int i = 1; i + 1 < m; ++i)
            d = euclid(d, ds[i + 1], euclidx[i], euclidy[i], n);
        
        int shift = best[d] / d;
        for(int i = m - 1; i >= 2; --i) {
            int coef = (long long)euclidy[i - 1] * shift % n;
            if(coef != 0)
                update(ds[i], coef);
            shift = (long long)shift * euclidx[i - 1] % n;
        }

        int coef = (long long)shift * euclidx[0] % n;
        if(coef != 0)
            update(ds[0], coef);

        coef = (long long)shift * euclidy[0] % n;
        if(coef != 0)
            update(ds[1], coef);
    
        int x, y;
        euclid(1, 2, x, y, n);
    }
}

