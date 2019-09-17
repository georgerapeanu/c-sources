#include <cstdio>
#include <map>
#include <iostream>

using namespace std;

const int NMAX = 1e5;
const int LEAFS = 3e5;
const long long inf = 1e17;
int n,k;
int a[NMAX + 5];
int b[NMAX + 5];
int c[NMAX + 5];
int d[NMAX + 5];

map<int,int> to_norm;
long long cost[NMAX + 5];
long long cost2[NMAX + 5];


long long aint[2 * LEAFS + 5];

void reset() {
    for(int i = 1; i <= 2 * LEAFS; i++) {
        aint[i] = inf;
    }
}

void update(int pos,long long val) {
    pos += LEAFS;
    for(aint[pos] = min(aint[pos],val); pos > 1; (pos >>= 1)) {
        aint[pos >> 1] = min(aint[pos >> 1],val);
    }
}

long long query(int l,int r) {
    long long ans = inf;
    r++;

    for(l += LEAFS,r += LEAFS; l < r; (l >>= 1),(r >>= 1)) {
        if(l & 1)ans = min(ans,aint[l++]);
        if(r & 1)ans = min(ans,aint[--r]);
    }

    return ans;
}

int main() {

    scanf("%d %d",&k,&n);

    for(int i = 1; i <= k; i++) {
        scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
        to_norm[a[i]] = 1;
        to_norm[b[i]] = 1;
        to_norm[c[i]] = 1;
    }

    to_norm[1] = 1;
    to_norm[n] = 1;

    int last = 0;
    for(auto &it:to_norm) {
        it.second = ++last;
    }

    reset();
    update(1,0);
    for(int i = 1; i <= k; i++) {
        cost[i] = d[i] + query(to_norm[a[i]],to_norm[b[i]]);
        update(to_norm[c[i]],cost[i]);
    }

    reset();
    update(to_norm[n],0);
    for(int i = 1; i <= k; i++) {
        cost2[i] = d[i] + query(to_norm[a[i]],to_norm[b[i]]);
        update(to_norm[c[i]],cost2[i]);
    }

    long long ans = inf;

    for(int i = 1; i <= k; i++) {
        ans = min(ans,cost[i] + cost2[i] - d[i]);
    }

    printf("%lld\n",(ans == inf ? -1:ans));

    return 0;
}
