#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;
const long long VMAX = 1e18;

struct query_t {
    int id;
    long long k;

    bool operator < (const query_t &other) {
        return k < other.k;
    }
};

int n,m,q;
int fr[NMAX + 5];
query_t queries[NMAX + 5];
pair<int,int> stuff[NMAX + 5];
int ans[NMAX + 5];



////wtf
class AIB {
public:
    int aib[int(1e6) + 5];

    void up(int pos) {
        for(; pos <= NMAX; pos += (-pos) & pos) {
            aib[pos]++;
        }
    }

    int get_kth(int k) {
        int sum = 0;
        int pos = 0;
        for(int t = 1 << 25; t; t >>= 1) {
            if(pos + t <= NMAX && sum + aib[pos + t] < k) {
                pos += t;
                sum += aib[pos];
            }
        }
        return pos + 1;
    }
};


int main() {

    scanf("%d %d %d",&n,&m,&q);

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d",&x);
        fr[x]++;
    }

    for(int i = 1; i <= q; i++) {
        queries[i].id = i;
        scanf("%lld",&queries[i].k);
    }


    for(int i = 1; i <= m; i++) {
        stuff[i] = {fr[i],i};
    }

    sort(stuff + 1,stuff + 1 + m);

    sort(queries + 1,queries + 1 + q);

    int ind = 1;
    long long delta = n;
    int cnt_active = 1;

    AIB aib;

    aib.up(stuff[1].second);

    for(int i = 1; i <= q; i++) {
        queries[i].k -= delta;
        while(ind < m && 1LL * (stuff[ind + 1].first - stuff[ind].first) * ind < queries[i].k) {
            delta += 1LL * (stuff[ind + 1].first - stuff[ind].first) * ind;
            queries[i].k -= 1LL * (stuff[ind + 1].first - stuff[ind].first) * ind;
            ind++;
            cnt_active++;
            aib.up(stuff[ind].second);
        }
        queries[i].k = (queries[i].k - 1) % cnt_active + 1;
        ans[queries[i].id] = aib.get_kth(queries[i].k);
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
