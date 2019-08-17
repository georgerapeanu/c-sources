#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("verkhoyansk.in","r");
FILE *g = fopen("verkhoyansk.out","w");

const int NMAX = 3e5;
const int QMAX = 6e5;

int n,q;
int v[NMAX + 5];
int nxt[NMAX + 5];
int lst[NMAX + 5];
int aib[NMAX + 5];
int ans[QMAX + 5];

vector<pair<int,int> > queries[NMAX + 5];

void update(int pos,int val) {
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] = max(aib[pos],val);
    }
}

int query(int pos) {
    int ans = 0;
    int tmp_ma = 0;

    for(int sh = 1 << 20; sh; sh >>= 1) {
        if(ans + sh <= n && max(tmp_ma,aib[ans + sh]) <= pos) {
            tmp_ma = max(tmp_ma,aib[ans + sh]);
            ans += sh;
        }
    }

    return ans + 1;
}

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        lst[i] = n + 1;
    }

    for(int i = n; i; i--) {
        nxt[i] = lst[v[i]];
        lst[v[i]] = i;
    }

    for(int i = 1; i <= q; i++) {
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        l++;
        r++;
        queries[l].push_back({r,i});
    }

    for(int i = 1; i <= n; i++) {
        update(i,lst[i]);
    }

    for(int i = 1; i <= n; i++) {
        for(auto it:queries[i]) {
            ans[it.second] = query(it.first);
        }
        update(v[i],nxt[i]);
    }

    for(int i = 1; i <= q; i++) {
        fprintf(g,"%d\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
