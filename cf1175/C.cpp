#include <bits/stdc++.h>

using namespace std;

const long long NMAX = 2e5;

long long t;
long long n,k;
long long v[NMAX + 5];

long long solve() {
    pair<long long,long long> best = {1LL << 60,-1};
    for(int i = 1; i <= n - k; i++) {
        long long pos = (v[i] + v[i + k]) / 2;
        long long cost = max(pos - v[i],v[i + k] - pos);
        best = min(best,make_pair(cost,pos));
    }
    return best.second;
}

int main() {

    scanf("%lld",&t);

    while(t--) {
        scanf("%lld %lld",&n,&k);
        for(long long i = 1; i <= n; i++) {
            scanf("%lld",&v[i]);
        }

        printf("%lld\n",solve());
    }

    return 0;
}
