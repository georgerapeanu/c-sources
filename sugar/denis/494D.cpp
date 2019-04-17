#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

struct node_t {
    int sum;
    int sum2;
    int lazy;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.sum = (this->sum + other.sum) % MOD;
        ans.sum2 = (this->sum2 + other.sum2) % MOD;
        ans.lazy = 0;
        return ans;
    }

    void add_val(int val,int st,int dr) {
        this->lazy = (this->lazy + val) % MOD;
        this->sum2 = (this->sum2 + 1LL * (1LL * val * val % MOD) * (dr - st + 1) + 2LL * val * this->sum) % MOD;
        this->sum = (this->sum + 1LL * val * (dr - st + 1)) % MOD;
    }
};

node_t aint[4 * NMAX + 5];
int init_d[NMAX + 5];
int lin[NMAX + 5],len;
int fst[NMAX + 5];
int lst[NMAX + 5];
int n,q;
int ans[NMAX + 5];
vector<pair<int,int> > graph[NMAX + 5];
vector<pair<int,int> > queries[NMAX + 5];

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod].lazy = 0;
        aint[nod].sum = init_d[lin[st]];
        aint[nod].sum2 = 1LL * init_d[lin[st]] * init_d[lin[st]] % MOD;
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == 0) {
        aint[nod].lazy = 0;
        return ;
    }

    int mid = (st + dr) / 2;

    aint[nod * 2].add_val(aint[nod].lazy,st,mid);
    aint[nod * 2 + 1].add_val(aint[nod].lazy,mid + 1,dr);

    aint[nod].lazy = 0;
}

void update(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod].add_val(val,st,dr);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

int query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);

    if(D < st || dr < S) {
        return 0;
    }

    if(S <= st && dr <= D) {
        return aint[nod].sum2;
    }

    int mid = (st + dr) / 2;

    return (query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D)) % MOD;
}

void predfs(int nod,int tata,int dist) {
    init_d[nod] = dist;

    lin[++len] = nod;
    fst[nod] = len;

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        predfs(it.first,nod,(dist + it.second) % MOD);
    }
    lst[nod] = len;
}

void dfs(int nod,int tata) {
    for(auto it:queries[nod]) {
        ans[it.second] = ((2 * query(1,1,n,fst[it.first],lst[it.first]) - query(1,1,n,1,n)) % MOD + MOD) % MOD;
    }

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        update(1,1,n,1,n,it.second);
        update(1,1,n,fst[it.first],lst[it.first],(2 * MOD - 2 * it.second) % MOD);

        dfs(it.first,nod);

        update(1,1,n,fst[it.first],lst[it.first],2 * it.second % MOD);
        update(1,1,n,1,n,(MOD - it.second) % MOD);
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        graph[x].push_back({y,z});
        graph[y].push_back({x,z});
    }

    predfs(1,0,0);
    build(1,1,n);

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        queries[u].push_back({v,i});
    }

    dfs(1,0);

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
