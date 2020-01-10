#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("calafat.in","r");
FILE *g = fopen("calafat.out","w");

const int NMAX = 2e5;
const int QMAX = 2e5;

int n,q;

struct query_t {
    int l,r;
    int id;

    bool operator < (const query_t &other)const {
        if(r != other.r) {
            return r < other.r;
        }
        return l < other.l;
    }
};

query_t query[NMAX + QMAX + 5];

long long aib[NMAX + 5];
long long ans[QMAX + 5];

void aib_update(int pos,int val) {
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

long long aib_query(int pos) {
    long long ans = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }

    return ans;
}


int last[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        int val;
        fscanf(f,"%d",&val);
        query[i] = {0,i,val};
    }

    for(int i = n + 1; i <= n + q; i++) {
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        query[i] = {l,r,i - n};
    }

    sort(query + 1,query + 1 + n + q);

    for(int i = 1; i <= n + q; i++) {
        if(query[i].l == 0) {
            if(last[query[i].id] > 0) {
                aib_update(last[query[i].id],query[i].r - last[query[i].id]);
            }
            last[query[i].id] = query[i].r;
        }
        else {
            ans[query[i].id] = aib_query(query[i].r) - aib_query(query[i].l - 1);
        }
    }

    for(int i = 1; i <= q; i++) {
        fprintf(g,"%lld\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
