#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;
const long long inf = 1e16;

struct query_t {
    int l,r,id;
};


int n,q;
vector<query_t> queries[NMAX + 5];
vector< pair<int,int> > graph[NMAX + 5];

long long aint[4 * NMAX + 5];
long long lazy[4 * NMAX + 5];

int lft[NMAX + 5];
int rgt[NMAX + 5];

long long ans[NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || lazy[nod] == 0) {
        return ;
    }

    aint[nod * 2] += lazy[nod];
    aint[2 * nod + 1] += lazy[nod];
    lazy[nod * 2] += lazy[nod];
    lazy[2 * nod + 1] += lazy[nod];
    lazy[nod] = 0;
}

void refresh(int nod,int st,int dr) {
    if(st == dr) {
        return;
    }
    aint[nod] = min(aint[2 * nod],aint[2 * nod + 1]);
}

void update(int nod,int st,int dr,int S,int D,long long val) {
    propag(nod,st,dr);

    if(st > D || dr < S) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod] += val;
        lazy[nod] += val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    refresh(nod,st,dr);
}

long long query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);

    if(st > D || dr < S) {
        return inf;
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    long long a = query(nod * 2,st,mid,S,D);
    long long b = query(nod * 2 + 1,mid + 1,dr,S,D);

    return min(a,b);
}

void predfs(int nod,long long dist = 0) {
    update(1,1,n,nod,nod,(graph[nod].size() == 0 ? dist:inf));

    lft[nod] = nod;
    rgt[nod] = nod;

    for(auto it:graph[nod]) {
        predfs(it.first,dist + it.second);
        rgt[nod] = max(rgt[nod],rgt[it.first]);
    }
}

void dfs(int nod) {
    for(auto it:queries[nod]) {
        ans[it.id] = query(1,1,n,it.l,it.r);
    }

    for(auto it:graph[nod]) {
        update(1,1,n,1,n,it.second);
        update(1,1,n,lft[it.first],rgt[it.first],-2 * it.second);
        dfs(it.first);
        update(1,1,n,1,n,-it.second);
        update(1,1,n,lft[it.first],rgt[it.first],2 * it.second);
    }
}

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 2; i <= n; i++) {
        int p,w;
        scanf("%d %d",&p,&w);
        graph[p].push_back({i,w});
    }

    for(int i = 1; i <= q; i++) {
        int x,l,r;
        scanf("%d %d %d",&x,&l,&r);
        queries[x].push_back({l,r,i});
    }

    predfs(1);

    dfs(1);

    for(int i = 1; i <= q; i++) {
        printf("%lld\n",ans[i]);
    }

    return 0;
}
