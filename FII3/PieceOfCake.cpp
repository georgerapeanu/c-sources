#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const long long VMAX = ((long long)1e6) * (3LL << 22);

int n;
long long v[2 * NMAX + 5];

long long gcd(long long a,long long b) {
    if(!b) {
        return a;
    }
    return gcd(b,a % b);
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%lld",&v[i]);
        v[i] *= (3LL << 22);

    }

    priority_queue<pair<long long,int> > h;

    long long mi = v[1];

    for(int i = 1; i <= n; i++) {
        h.push({v[i],i});
        mi = min(mi,v[i]);
    }

    long long ans[] = {0,0};
    int l = 0;

    while(!h.empty()) {
        long long val = h.top().first;
        int ind = h.top().second;
        h.pop();

        if(val < 2 * mi) {
            continue;
        }

        val /= 2;
        ans[l] += val;
        l ^= 1;

        mi = min(val,mi);

        h.push({val,ind});
        v[ind] = val;
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    if(n % 2 == 0) {
        for(int i = 1; i <= n; i++) {
            ans[l] += v[i];
            l ^= 1;
        }
    }
    else {
        for(int i = 1; i <= n; i++) {
            ans[l] += 2 * v[i] / 3;
            ans[l ^ 1] += v[i] / 3;
            l ^= 1;
        }
    }

    for(int i = 0; i < 2; i++) {
        long long num = 3LL << 22;
        long long g = gcd(ans[i],num);
        printf("%lld/%lld\n",ans[i] / g,num / g);
    }

    return 0;
}
