#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n,m,q;
pair<int,int> edge[NMAX + 5];
vector<int> graph[NMAX + 5];
int fa[NMAX + 5];

int fst[NMAX + 5];
int lst[NMAX + 5];
int len;

int aint[4 * NMAX + 5];
bool used[NMAX + 5];

int dp[NMAX + 5];
int taken_father[NMAX + 5];
int lin[NMAX + 5];

void predfs(int nod,int tata) {
    fst[nod] = ++len;
    lin[len] = nod;
    fa[nod] = tata;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
    }

    lst[nod] = len;
}

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod] = lst[lin[st]];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

int query(int nod,int st,int dr,int l,int r,int val) {
    if(r < st || l > dr || aint[nod] < val) {
        return 0;
    }

    if(l <= st && dr <= r) {
        if(st == dr) {
            return st;
        }
        else if(aint[2 * nod + 1] >= val) {
            return query(nod * 2 + 1,(st + dr) / 2 + 1,dr,l,r,val);
        }
        else {
            return query(nod * 2,st,(st + dr) / 2,l,r,val);
        }
    }

    int mid = (st + dr) / 2;
    return max(query(nod * 2,st,mid,l,r,val),query(nod * 2 + 1,mid + 1,dr,l,r,val));
}

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod] = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

inline int get_root(int nod) {
    return lin[query(1,1,n,1,fst[nod],lst[nod])];
}

int main() {

    scanf("%d %d %d",&n,&m,&q);

    for(int i = 1; i < n; i++) {
        scanf("%d %d",&edge[i].first,&edge[i].second);
        graph[edge[i].first].push_back(edge[i].second);
        graph[edge[i].second].push_back(edge[i].first);
    }

    for(int i = 1; i <= n; i++) {
        dp[i] = 1;
        taken_father[i] = 0;
    }

    predfs(1,0);
    build(1,1,n);

    while(m--) {
        int x;
        scanf("%d",&x);

        int ch = (edge[x].first == fa[edge[x].second] ? edge[x].second:edge[x].first);
        int root = get_root(fa[ch]);

        if(used[x] == false) {
            dp[root] += dp[ch] - taken_father[ch];
            used[x] = true;
            update(1,1,n,fst[ch],0);
        }
        else {
            used[x] = false;
            dp[ch] = taken_father[ch] = dp[root];
            update(1,1,n,fst[ch],lst[ch]);
        }
    }

    while(q--) {
        int x;
        scanf("%d",&x);
        printf("%d\n",dp[get_root(x)]);
    }

    return 0;
}
