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
}

// Q = 1
// Here we do not know how to solve an equation of the type:
// ds[0] * x[0] + ds[1] * x[1] + ... + ds[m - 1] * x[m - 1] = k
// where k is any variable
// To solve this, we can build the following graph:
// We have n nodes labeled from 0 to n - 1
// For each x from 0 to n - 1, we will create an edge from x to (x + ds[i]) % n
// with the label ds[i] for every i from 0 to m - 1
// Now we need to find a path from 0 to k. x[0] will be the number of edges with the label
// ds[0] on our path, x[1] will be the number of edges with the label ds[1] and so on.
// Since we know every path from 0 to every number k, we can see which one is optimal

int father_edge[MAX_N];
bool vis[MAX_N];
int x[MAX_D], *ds;

void dfs(int nod, int m) {
    for(int i = 0; i < m; ++i) {
        int dest = (nod + ds[i]) % _n;
        if(!vis[dest]) {
            vis[dest] = true;
            father_edge[dest] = i;
            dfs(dest, m);
        }
    }
}

void query(int m,const int _ds[]) {
    ds = new int[m];
    for(int i = 0;i < m;i++){
        ds[i] = _ds[i];
    }
    int best_inv = 0;
    for(int i = 0; i < _n; ++i)
        if(nr_inv[i] < nr_inv[best_inv])
            best_inv = i;

    while(best_inv != 0) {
        x[father_edge[best_inv]]++;
        best_inv = (best_inv - ds[father_edge[best_inv]] + _n) % _n;
    }
    
    for(int i = 0; i < m; ++i) {
        x[i] = x[i] % (_n / ds[i]);
        if(x[i] != 0)
            update(ds[i], x[i]);
    }
}

