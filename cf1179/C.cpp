#include <bits/stdc++.h>

using namespace std;

int n,m,q;
int a[int(3e5) + 5];
int b[int(3e5) + 5];

struct node_t {
    int lazy;
    int mi;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.lazy = 0;
        ans.mi = min(mi,other.mi);
        return ans;
    }
};

node_t aint[int(4e6) + 5];

void propag(int nod,int st,int dr) {
    if(aint[nod].lazy == 0 || st == dr) {
        return ;
    }
    aint[2 * nod].lazy += aint[nod].lazy;
    aint[2 * nod + 1].lazy += aint[nod].lazy;
    aint[2 * nod].mi += aint[nod].lazy;
    aint[2 * nod + 1].mi += aint[nod].lazy;
    aint[nod].lazy = 0;
}

void update(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);

    if(S <= st && dr <= D) {
        aint[nod].lazy += val;
        aint[nod].mi += val;
        return ;
    }

    if(D < st || S > dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

int fi_neg_pos(int nod,int st,int dr) {
    propag(nod,st,dr);
    if(st == dr) {
        return (aint[nod].mi < 0 ? st : -1);
    }
    int mid = (st + dr) / 2;
    if(aint[2 * nod + 1].mi < 0) {
        return fi_neg_pos(nod * 2 + 1,mid + 1,dr);
    }
    return fi_neg_pos(nod * 2,st,mid);
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        update(1,1,1e6,1,a[i],-1);
    }

    for(int i = 1; i <= m; i++) {
        scanf("%d",&b[i]);
        update(1,1,1e6,1,b[i],1);
    }

    scanf("%d",&q);

    while(q--) {
        int t,i,x;
        scanf("%d %d %d",&t,&i,&x);

        if(t == 1) {
            update(1,1,1e6,1,a[i],1);
            a[i] = x;
            update(1,1,1e6,1,a[i],-1);
        }
        else {
            update(1,1,1e6,1,b[i],-1);
            b[i] = x;
            update(1,1,1e6,1,b[i],1);
        }
        printf("%d\n",fi_neg_pos(1,1,1e6));
    }

    return 0;
}
