#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;
const int QMAX = 5e5;

struct node_t {
    int sum;
    int suf_sum;

    node_t(int sum = 0,int suf_sum = 0) {
        this->sum = sum;
        this->suf_sum = suf_sum;
    }

    node_t join(node_t &other) {
        return node_t(sum + other.sum,min(other.suf_sum,suf_sum + other.sum));
    }
};

struct query_t {
    int r,ind;
};

node_t aint[4 * NMAX + 5];

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].sum += val;
        aint[nod].suf_sum += val;
        return;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}

node_t query(int nod,int st,int dr,int S,int D) {
    if(st > D || dr < S) {
        return {0,0};
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    node_t a = query(nod * 2,st,mid,S,D);
    node_t b = query(nod * 2 + 1,mid + 1,dr,S,D);

    return a.join(b);
}

int n,q;
int ans[QMAX + 5];
char c[NMAX + 5];
vector<query_t> queries[NMAX + 5];

int non_active[NMAX + 5],len;

int main() {

    scanf("%d\n",&n);
    fgets(c + 1,NMAX + 5,stdin);
    scanf("%d\n",&q);

    for(int i = 1; i <= q; i++) {
        int l,r;
        scanf("%d %d\n",&l,&r);
        queries[l].push_back({r,i});
    }

    for(int i = n; i; i--) {
        if(c[i] == 'T') {
            non_active[++len] = i;
        }
        else {
            update(1,1,n,i,1);
            if(len) {
                update(1,1,n,non_active[len],-1);
                len--;
            }
        }
        for(auto it:queries[i]) {
            int tmp = max(0,-query(1,1,n,i,it.r).suf_sum);
            int st = 0,dr = len + 1;
            while(dr - st > 1) {
                int mid = (st + dr) / 2;
                if(non_active[mid] <= it.r) {
                    dr = mid;
                }
                else {
                    st = mid;
                }
            }
            tmp += len - st;
            ans[it.ind] = tmp;
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
