#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e6;

int n,d;
int l[NMAX + 5];
int p[NMAX + 5];
int s[NMAX + 5];
int t[NMAX + 5];
int nxt[NMAX + 5];

namespace greedy1 {
long long solve() {
    int pos = 1;
    long long ti = 0;
    vector<pair<long long,int> > v;

    for(int i = 1; i <= n; i++) {
        v.push_back({p[i] + 1LL * d * i,i});
        v.push_back({l[i] + 1LL * d * i,-i});
    }

    sort(v.begin(),v.end());

    int last = 1;

    for(auto it:v) {
        if(it.second < 0) {
            last = max(-it.second,last);
        }
        else {
            nxt[it.second] = last;
        }
    }

    nxt[n] = n + 1;

    while(pos <= n) {
        if(nxt[pos] <= pos) {
            return -1;
        }
        if(ti < s[pos]) {
            ti = s[pos];
        }
        else {
            ti = s[pos] + ((ti - s[pos]) / t[pos] + 1) * t[pos];
        }
        pos = nxt[pos];
    }

    return ti;
}
}

int main() {

    scanf("%d %d",&n,&d);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d %d",&l[i],&p[i],&s[i],&t[i]);
    }

    printf("%lld\n",greedy1::solve());

    return 0;
}
