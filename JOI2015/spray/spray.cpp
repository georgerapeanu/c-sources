#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

struct node_t {
    long long sum;
    int cnt;
    int mi;
    int ma;
    int lazy;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.sum = this->sum + other.sum;
        ans.cnt = this->cnt + other.cnt;
        ans.mi = min(this->mi,other.mi);
        ans.ma = max(this->ma,other.ma);
        ans.lazy = 0;
        return ans;
    }
};

int n,q,k;

node_t aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }

    aint[2 * nod].lazy += aint[nod].lazy;
    aint[2 * nod].mi += aint[nod].lazy;
    aint[2 * nod].ma += aint[nod].lazy;
    aint[2 * nod].sum += 1LL * aint[2 * nod].cnt * aint[nod].lazy;

    aint[2 * nod + 1].lazy += aint[nod].lazy;
    aint[2 * nod + 1].mi += aint[nod].lazy;
    aint[2 * nod + 1].ma += aint[nod].lazy;
    aint[2 * nod + 1].sum += 1LL * aint[2 * nod + 1].cnt * aint[nod].lazy;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr) {
    if(st == dr) {
        int val;
        scanf("%d",&val);
        aint[nod].sum = aint[nod].mi = aint[nod].ma = val;
        aint[nod].cnt = 1;
        aint[nod].lazy = 0;
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_pos(int nod,int st,int dr,int pos,int val) {
    propag(nod,st,dr);

    if(st > pos || dr < pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].sum = aint[nod].mi = aint[nod].ma = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_pos(nod * 2,st,mid,pos,val);
    update_pos(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_range(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(dr < l || st > r) {
        return ;
    }

    if(l <= st && dr <= r && aint[nod].ma - (aint[nod].ma / k) == aint[nod].mi - (aint[nod].mi / k)) {
        aint[nod].lazy += -aint[nod].ma + (aint[nod].ma / k);
        aint[nod].mi += -aint[nod].ma + (aint[nod].ma / k);
        aint[nod].sum += 1LL * aint[nod].cnt * (-aint[nod].ma + (aint[nod].ma / k));
        aint[nod].ma += -aint[nod].ma + (aint[nod].ma / k);
        return ;
    }

    int mid = (st + dr) / 2;

    update_range(nod * 2,st,mid,l,r);
    update_range(nod * 2 + 1,mid + 1,dr,l,r);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

long long query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(dr < l || st > r) {
        return 0;
    }

    if(l <= st && dr <= r) {
        return aint[nod].sum;
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
}

int main() {

    scanf("%d %d %d",&n,&q,&k);

    build(1,1,n);

    while(q--) {
        int t,a,b;

        scanf("%d %d %d",&t,&a,&b);

        if(t == 1) {
            update_pos(1,1,n,a,b);
        }
        else if(t == 2) {
            update_range(1,1,n,a,b);
        }
        else {
            printf("%lld\n",query(1,1,n,a,b));
        }
    }

    return 0;
}

