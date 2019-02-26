#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("kth.in","r");
FILE *g = fopen("kth.out","w");

const int NMAX = 1e5;
int n,q;

struct node_t {
    int mi;
    int ma;
    int lazy;

    node_t operator + (const node_t &other)const {
        node_t ans = *this;
        ans.mi = min(ans.mi,other.mi);
        ans.ma = max(ans.ma,other.ma);
        ans.lazy = 0;
        return ans;
    }
} aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(aint[nod].lazy == 0) {
        return ;
    }

    if(st == dr) {
        aint[nod].lazy = 0;
        return;
    }

    aint[2 * nod].mi = aint[2 * nod].ma = aint[2 * nod].lazy = aint[nod].lazy;
    aint[2 * nod + 1].mi = aint[2 * nod + 1].ma = aint[2 * nod + 1].lazy = aint[nod].lazy;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr) {
    aint[nod].lazy = 0;

    if(st == dr) {
        int val;
        fscanf(f,"%d",&val);
        aint[nod].mi = aint[nod].ma = val;
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void update_set(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod].lazy = aint[nod].mi = aint[nod].ma = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_set(nod * 2,st,mid,S,D,val);
    update_set(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void get_intervals(int nod,int st,int dr,int S,int D,vector<pair<int,int> > &ans) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D && aint[nod].mi == aint[nod].ma) {
        ans.push_back({aint[nod].mi,dr - st + 1});
        return ;
    }

    int mid = (st + dr) / 2;

    get_intervals(nod * 2,st,mid,S,D,ans);
    get_intervals(nod * 2 + 1,mid + 1,dr,S,D,ans);
}

void set_kth(int l,int r,int k) {
    int val;
    vector< pair<int,int> > v;
    get_intervals(1,1,n,l,r,v);
    sort(v.begin(),v.end());
    for(auto it:v) {
        if(k > it.second) {
            k -= it.second;
        }
        else {
            val = it.first;
            break;
        }
    }
    update_set(1,1,n,l,r,val);
}

void afis(int nod,int st,int dr) {
    propag(nod,st,dr);

    if(st == dr) {
        fprintf(g,"%d ",aint[nod].mi);
        return ;
    }

    int mid = (st + dr) / 2;

    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

int main() {

    fscanf(f,"%d %d",&n,&q);

    build(1,1,n);

    while(q--) {
        int t,l,r,k;
        fscanf(f,"%d %d %d %d",&t,&l,&r,&k);

        if(t == 1) {
            update_set(1,1,n,l,r,k);
        }
        else {
            set_kth(l,r,k);
        }
    }

    afis(1,1,n);

    return 0;
}
