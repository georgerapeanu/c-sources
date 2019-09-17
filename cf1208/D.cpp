#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
int ans[NMAX + 5];

struct node_t{
    long long lazy;
    long long lo,hi;

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.lazy = 0;
        ans.lo = min(this->lo,other.lo);
        ans.hi = max(this->hi,ans.hi);
        return ans;
    }

}aint[4 * NMAX + 5];

void propag(int nod,int st,int dr){
    if(st == dr || aint[nod].lazy == 0){
        return ;
    }
    aint[2 * nod].lazy += aint[nod].lazy;
    aint[2 * nod].lo += aint[nod].lazy;
    aint[2 * nod].hi += aint[nod].lazy;
    aint[2 * nod + 1].lazy += aint[nod].lazy;
    aint[2 * nod + 1].lo += aint[nod].lazy;
    aint[2 * nod + 1].hi += aint[nod].lazy;
    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr){
    if(st == dr){
        long long val;
        scanf("%lld",&val);
        aint[nod].lazy = 0;
        aint[nod].lo = aint[nod].hi = val;
        return ;
    }

    int mid = (st + dr) / 2;
    
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_delta(int nod,int st,int dr,int l,int r,int val){
    propag(nod,st,dr);

    if(r < st || l > dr){
        return ;
    }

    if(l <= st && dr <= r){
        aint[nod].lazy += val;
        aint[nod].lo += val;
        aint[nod].hi += val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_delta(nod * 2,st,mid,l,r,val);
    update_delta(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int query(int nod,int st,int dr){
    propag(nod,st,dr);

    if(st == dr){
        aint[nod] = {0,(1LL << 62),(1LL << 62)};
        return st;
    }
    if(aint[nod * 2 + 1].lo == 0){
        int tmp = query(nod * 2 + 1,(st + dr) / 2 + 1,dr);
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
        return tmp;
    }
    else{
        int tmp = query(nod * 2,st,(st + dr) / 2);
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
        return tmp;
    }
}

int main() {

    scanf("%d",&n);
    build(1,1,n);

    for(int i = 1;i <= n;i++){
        int pos = query(1,1,n);
        update_delta(1,1,n,pos + 1,n,-i);
        ans[pos] = i;
    }

    for(int i = 1;i <= n;i++){
        printf("%d ",ans[i]);
    }

    return 0;
}
