#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int KMAX = 2e5;
int n,m,k,q;

vector<int> points[NMAX + 5];

struct query_t {
    int x,y,xx,yy;
    int id;

    bool operator < (const query_t &other) {
        if(x != other.x) {
            return x < other.x;
        }
        if(xx != other.xx) {
            return xx < other.xx;
        }
        if(y != other.y) {
            return y < other.y;
        }
        if(yy != other.yy) {
            return yy < other.yy;
        }
        return id < other.id;
    }
};

pair<int,int> edges[KMAX + 5];
query_t queries[KMAX + 5];
int ans[KMAX + 5];

int aint[4 * NMAX + 5];

void build(int nod,int st,int dr) {
    aint[nod] = NMAX + 5;

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
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
    aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
}

int query(int nod,int st,int dr,int S,int D) {
    if(D < st || dr < S) {
        return 0;
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,S,D),query(2 * nod + 1,mid + 1,dr,S,D));
}

void solve() {
    sort(queries + 1,queries + 1 + q);
    reverse(queries + 1,queries + 1 + q);
    int medgex = 0;
    for(int i = 1; i <= k; i++) {
        points[edges[i].first].push_back(edges[i].second);
        medgex = max(medgex,edges[i].first);
    }

    build(1,1,n);

    int lastx = max(queries[1].x + 1,medgex + 1);

    for(int i = 1; i <= q; i++) {
        while(lastx > queries[i].x) {
            lastx--;
            for(auto it:points[lastx]) {
                update(1,1,n,it,lastx);
            }
        }
        int tmp = query(1,1,n,queries[i].y,queries[i].yy);
        ans[queries[i].id] |= (tmp <= queries[i].xx);
    }

    for(int i = 1; i <= NMAX; i++) {
        points[i].clear();
    }
}

void flip() {
    swap(n,m);
    for(int i = 1; i <= k; i++) {
        swap(edges[i].first,edges[i].second);
    }

    for(int i = 1; i <= q; i++) {
        swap(queries[i].x,queries[i].y);
        swap(queries[i].xx,queries[i].yy);
    }
}

int main() {

    scanf("%d %d %d %d",&m,&n,&k,&q);

    for(int i = 1; i <= k; i++) {
        scanf("%d %d",&edges[i].first,&edges[i].second);
    }

    for(int i = 1; i <= q; i++) {
        scanf("%d %d %d %d",&queries[i].x,&queries[i].y,&queries[i].xx,&queries[i].yy);
        queries[i].id = i;
    }

    solve();
    flip();
    solve();

    for(int i = 1; i <= q; i++) {
        printf("%s\n",(ans[i] == true ? "YES":"NO"));
    }

    return 0;
}
