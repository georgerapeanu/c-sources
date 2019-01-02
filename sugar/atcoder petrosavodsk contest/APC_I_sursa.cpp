#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;

pair<int,int> aint[4 * NMAX + 5];
int lazy[4 * NMAX + 5];

void build(int nod,int st,int dr,int a[]) {
    if(st == dr) {
        aint[nod] = {a[st],a[st]};
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid,a);
    build(nod * 2 + 1,mid + 1,dr,a);
    aint[nod].first = min(aint[2 * nod].first,aint[2 * nod + 1].first);
    aint[nod].second = max(aint[2 * nod].second,aint[2 * nod + 1].second);
}

void propag(int nod,int st,int dr) {
    if(st == dr || !lazy[nod]) {
        return ;
    }

    lazy[2 * nod] += lazy[nod];
    aint[2 * nod].first += lazy[nod];
    aint[2 * nod].second += lazy[nod];
    lazy[2 * nod + 1] += lazy[nod];
    aint[2 * nod + 1].first += lazy[nod];
    aint[2 * nod + 1].second += lazy[nod];
    lazy[nod] = 0;
}

void add(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);
    if(dr < S || st > D) {
        return ;
    }
    if(S <= st && dr <= D) {
        aint[nod].first += val;
        aint[nod].second += val;
        lazy[nod] += val;
        return;
    }
    int mid = (st + dr) / 2;
    add(nod * 2,st,mid,S,D,val);
    add(nod * 2 + 1,mid + 1,dr,S,D,val);
    aint[nod].first = min(aint[2 * nod].first,aint[2 * nod + 1].first);
    aint[nod].second = max(aint[2 * nod].second,aint[2 * nod + 1].second);
}

void divi(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);
    if(dr < S || st > D) {
        return ;
    }
    if(S <= st && dr <= D && aint[nod].second - aint[nod].first == aint[nod].second / val - aint[nod].first / val) {
        lazy[nod] += aint[nod].first / val - aint[nod].first;
        aint[nod].second += aint[nod].first / val - aint[nod].first;
        aint[nod].first += aint[nod].first / val - aint[nod].first;
        return;
    }
    int mid = (st + dr) / 2;
    divi(nod * 2,st,mid,S,D,val);
    divi(nod * 2 + 1,mid + 1,dr,S,D,val);
    aint[nod].first = min(aint[2 * nod].first,aint[2 * nod + 1].first);
    aint[nod].second = max(aint[2 * nod].second,aint[2 * nod + 1].second);
}

int query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);
    if(dr < S || st > D) {
        return 0;
    }
    if(S <= st && dr <= D) {
        return aint[nod].second;
    }
    int mid = (st + dr) / 2;
    return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
}

int n,q;
int a[200005];

int main() {

    freopen("in","r",stdin);
    freopen("out","w",stdout);

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    build(1,1,n,a);

    while(q--) {
        int t,l,r,x;

        scanf("%d %d %d %d",&t,&l,&r,&x);
        l++;
        r++;

        if(t == 0) {
            add(1,1,n,l,r,x);
        }

        else if(t == 1) {
            divi(1,1,n,l,r,x);
        }

        else {
            printf("%d\n",query(1,1,n,l,r));
        }
    }

    return 0;
}