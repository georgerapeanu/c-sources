#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("task1.in","r");
FILE *g = fopen("task1.out","w");

const int NMAX = 1e6;
const int VMAX = 1e9;
const int inf = VMAX + 5;

struct node_t {

    vector< pair<int,int> > v;

    long long sum = 0;
    long long lazy = 0;

    node_t join(const node_t &other)const {
        node_t ans;

        ans.v = v;

        for(auto it:other.v) {
            ans.v.push_back(it);
        }

        sort(ans.v.begin(),ans.v.end());

        int l = 0;

        for(int i = 1; i < (int)ans.v.size(); i++) {
            if(ans.v[i].first != ans.v[l].first) {
                l++;
                ans.v[l].first = ans.v[i].first;
            }
            ans.v[l].second += ans.v[i].second;
        }

        ans.v.resize(2);

        ans.sum = sum + other.sum;

        return ans;
    }
} aint[4 * NMAX + 5];


void propag(int nod,int st,int dr) {
    if(aint[nod].lazy == 0 || st == dr) {
        return ;
    }

    if(aint[2 * nod].v[0].first <= aint[2 * nod + 1].v[0].first) {
        aint[2 * nod].v[0].first += aint[nod].lazy;
        aint[2 * nod].sum += 1LL * aint[nod].lazy * aint[2 * nod].v[0].second;
        aint[2 * nod].lazy += aint[nod].lazy;
    }

    if(aint[2 * nod].v[0].first >= aint[2 * nod + 1].v[0].first) {
        aint[2 * nod + 1].v[0].first += aint[nod].lazy;
        aint[2 * nod + 1].sum += 1LL * aint[nod].lazy * aint[2 * nod + 1].v[0].second;
        aint[2 * nod + 1].lazy += aint[nod].lazy;
    }

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr,int v[]) {
    aint[nod].sum = 0;
    aint[nod].lazy = 0;
    aint[nod].v = {{inf - 1,0},{inf,0}};

    if(st == dr) {
        aint[nod].v[0] = {v[st],1};
        aint[nod].sum = v[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid,v);
    build(nod * 2 + 1,mid + 1,dr,v);

    aint[nod] = aint[nod * 2].join(aint[2 * nod + 1]);
}

void update(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        if(val < aint[nod].v[0].first) {
            return;
        }

        if(val < aint[nod].v[1].first) {
            aint[nod].lazy += val - aint[nod].v[0].first;
            aint[nod].sum += 1LL * (val - aint[nod].v[0].first) * aint[nod].v[0].second;
            aint[nod].v[0].first = val;
            return ;
        }
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}

long long query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return 0;
    }

    if(S <= st && dr <= D) {
        return aint[nod].sum;
    }

    int mid = (st + dr) / 2;
    long long a = query(nod * 2,st,mid,S,D);
    long long b = query(nod * 2 + 1,mid + 1,dr,S,D);

    return a + b;
}

int n,q;
int v[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    build(1,1,n,v);

    while(q--) {
        int t,l,r;

        fscanf(f,"%d %d %d",&t,&l,&r);

        if(t == 1) {
            int x;
            fscanf(f,"%d",&x);
            update(1,1,n,l,r,x);
        }
        else {
            fprintf(g,"%lld\n",query(1,1,n,l,r));
        }
    }

    return 0;
}
