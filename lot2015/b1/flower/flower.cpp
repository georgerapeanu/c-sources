#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("flower.in","r");
FILE *g = fopen("flower.out","w");

const int NMAX = 2e5;
const long long inf = 1e17;
const pair<long long,long long> NASPA = {0,0};
int n,m;

struct node_t {
    pair<long long,long long> lazy;
    long long mi;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.lazy = NASPA;
        ans.mi = min(this->mi,other.mi);
        return ans;
    }

} aint[4 * NMAX + 5];

void init(int nod,int st,int dr) {
    aint[nod].lazy = NASPA;
    aint[nod].mi = -inf;

    if(st == dr) {
        return;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == NASPA) {
        return ;
    }

    int mid = (st + dr) / 2;

    aint[2 * nod].mi = min(aint[nod].lazy.first * st,aint[nod].lazy.first * mid) + aint[nod].lazy.second;
    aint[2 * nod + 1].mi = min(aint[nod].lazy.first * (mid + 1),aint[nod].lazy.first * dr) + aint[nod].lazy.second;
    aint[2 * nod].lazy = aint[nod].lazy;
    aint[2 * nod + 1].lazy = aint[nod].lazy;
    aint[nod].lazy = NASPA;
}

long long access(int nod,int st,int dr,int pos) {
    propag(nod,st,dr);

    if(st == dr) {
        return aint[nod].mi;
    }

    int mid = (st + dr) / 2;

    if(pos <= mid) {
        return access(nod * 2,st,mid,pos);
    }
    else {
        return access(nod * 2 + 1,mid + 1,dr,pos);
    }
}

void update(int nod,int st,int dr,long long valst,long long valdr,int l,int r,pair<long long,long long> seg) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }
    int mid = (st + dr) / 2;
    if(l <= st && dr <= r) {
        if(valst == inf + 2) {
            valst = access(nod,st,dr,st);
        }
        if(valdr == inf + 2) {
            valdr = access(nod,st,dr,dr);
        }
        if(valst <= seg.first * st + seg.second && valdr <= seg.first * dr + seg.second) {
            aint[nod].lazy = seg;
            aint[nod].mi = min(seg.first * st + seg.second,seg.first * dr + seg.second);
            return ;
        }
        if(st == dr) {
            return ;
        }
        long long a = access(nod,st,dr,mid);
        long long b = access(nod,st,dr,mid + 1);
        if(valst <= seg.first * st + seg.second || a <= seg.first * mid + seg.second) {
            update(nod * 2,st,mid,valst,a,l,r,seg);
        }
        if(valdr <= seg.first * dr + seg.second || b <= seg.first * (mid + 1) + seg.second) {
            update(nod * 2 + 1,mid + 1,dr,b,valdr,l,r,seg);
        }
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
        return ;
    }
    update(nod * 2,st,mid,valst,inf + 2,l,r,seg);
    update(nod * 2 + 1,mid + 1,dr,inf + 2,valdr,l,r,seg);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

long long query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return inf;
    }
    if(l <= st && dr <= r) {
        return aint[nod].mi;
    }

    int mid = (st + dr) / 2;

    return min(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
}

void afis(int nod,int st,int dr) {
    propag(nod,st,dr);

    printf("%d %d %d %lld %lld %lld\n",nod,st,dr,aint[nod].mi,aint[nod].lazy.first,aint[nod].lazy.second);

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    init(1,1,n);

    while(m--) {
        int t;
        fscanf(f,"%d ",&t);

        if(t == 1) {
            int c,a,p;
            fscanf(f,"%d %d %d",&c,&a,&p);

            pair<long long,long long> tmp;

            tmp = {p,a - 1LL * p * c};
            update(1,1,n,inf + 2,inf + 2,1,c,tmp);

            tmp = {-p,a + 1LL * p * c};
            update(1,1,n,inf + 2,inf + 2,c,n,tmp);
        }
        else {
            int l,r;
            fscanf(f,"%d %d",&l,&r);
            fprintf(g,"%lld\n",query(1,1,n,l,r));
        }
//        printf("\n\n\nafis\n");
//        afis(1,1,n);
    }

    fclose(f);
    fclose(g);

    return 0;
}
