#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;
const int QMAX = 5e5;

int n,q;
int d[NMAX + 5];

struct query_t {
    int t,l,r;
    int ans;
    int id;

    bool operator < (const query_t &other)const {
        if(t < other.t) {
            return t < other.t;
        }
        return id < other.id;
    }

} query[NMAX + 5];

int aib[NMAX + 5];

void aib_update(int pos,int val) {
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int aib_query(int pos) {
    int ans = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }

    return ans;
}

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&d[i]);
    }

    for(int i = 2; i <= n; i++) {
        d[i] = ((d[i] / d[i - 1]) + (d[i] % d[i - 1] != 0)) * d[i - 1];
    }

    for(int i = 1; i <= q; i++) {
        scanf("%d %d %d",&query[i].t,&query[i].l,&query[i].r);
        query[i].id = i;
        query[i].ans += (query[i].l <= query[i].t && query[i].t <= query[i].r);
    }

    vector<int> pos = {1};
    for(int i = 2; i <= n + 1; i++) {
        if(i == n + 1 || d[i] != d[i - 1]) {
            int per = d[i - 1];

            for(auto it:pos) {
                aib_update(it,1);
            }

            for(int i = 1; i <= q; i++) {
                int l = query[i].l - (query[i].t / per) * per;
                int r = query[i].r - (query[i].t / per) * per;
                r = min(r,-1);
                l = max(l,-n);
                if(l <= r) {
                    l = -l;
                    r = -r;
                    query[i].ans += aib_query(l) - aib_query(r - 1);

                }
            }

            for(auto it:pos) {
                aib_update(it,-1);
            }

            pos.clear();
        }
        pos.push_back(i);
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",query[i].ans);
    }

    return 0;
}
