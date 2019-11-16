#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
const int QMAX = 2e5;
const int NASPA = 1e9 + 5;

int n,q;
int h[NMAX + 5];
int a[NMAX + 5];
int b[NMAX + 5];
int ans[QMAX + 5];

vector<pair<int,int> >  queries[NMAX + 5];
vector<int> add[NMAX + 5];
vector<int> rem[NMAX + 5];

struct node_t {
    int ma_lazy;
    int mi_lazy;
    int best_ans;
    int mi_val;
    int ma_val;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.ma_lazy = ans.mi_lazy = NASPA;
        ans.best_ans = max(this->best_ans,other.best_ans);
        ans.mi_val = (this->mi_val == NASPA ? other.mi_val:(other.mi_val == NASPA ? this->mi_val:min(this->mi_val,other.mi_val)));
        ans.ma_val = (this->ma_val == NASPA ? other.ma_val:(other.ma_val == NASPA ? this->ma_val:max(this->ma_val,other.ma_val)));
        return ans;
    }

    void recalc_best_ans() {
        if(mi_val != NASPA) {
            if(mi_lazy != NASPA) {
                best_ans = max(best_ans,abs(mi_val - mi_lazy));
            }
            if(ma_lazy != NASPA) {
                best_ans = max(best_ans,abs(mi_val - ma_lazy));
            }
        }
        if(ma_val != NASPA) {
            if(mi_lazy != NASPA) {
                best_ans = max(best_ans,abs(ma_val - mi_lazy));
            }
            if(ma_lazy != NASPA) {
                best_ans = max(best_ans,abs(ma_val - ma_lazy));
            }
        }
    }

} aint[4 * NMAX + 5];

void init(int nod,int st,int dr) {
    aint[nod].ma_lazy = NASPA;
    aint[nod].mi_lazy = NASPA;
    aint[nod].best_ans = -1;
    aint[nod].mi_val = NASPA;
    aint[nod].ma_val = NASPA;

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].mi_lazy == NASPA) {
        aint[nod].mi_lazy = NASPA;
        aint[nod].ma_lazy = NASPA;
        return ;
    }

    aint[nod * 2].mi_lazy = (aint[nod * 2].mi_lazy == NASPA ? aint[nod].mi_lazy:min(aint[nod * 2].mi_lazy,aint[nod].mi_lazy));
    aint[nod * 2].ma_lazy = (aint[nod * 2].ma_lazy == NASPA ? aint[nod].ma_lazy:max(aint[nod * 2].ma_lazy,aint[nod].ma_lazy));
    aint[nod * 2 + 1].mi_lazy = (aint[nod * 2 + 1].mi_lazy == NASPA ? aint[nod].mi_lazy:min(aint[nod * 2 + 1].mi_lazy,aint[nod].mi_lazy));
    aint[nod * 2 + 1].ma_lazy = (aint[nod * 2 + 1].ma_lazy == NASPA ? aint[nod].ma_lazy:max(aint[nod * 2 + 1].ma_lazy,aint[nod].ma_lazy));

    aint[nod * 2].recalc_best_ans();
    aint[nod * 2 + 1].recalc_best_ans();

    aint[nod].mi_lazy = NASPA;
    aint[nod].ma_lazy = NASPA;
}

void update_best_ans(int nod,int st,int dr,int l,int r,int val) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }
    if(l <= st && dr <= r) {
        aint[nod].mi_lazy = val;
        aint[nod].ma_lazy = val;
        aint[nod].recalc_best_ans();
        return ;
    }

    int mid = (st + dr) / 2;

    update_best_ans(nod * 2,st,mid,l,r,val);
    update_best_ans(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int pos,int val) {
    propag(nod,st,dr);
    if(pos > dr || pos < st) {
        return ;
    }

    if(st == dr) {
        aint[nod].mi_val = aint[nod].ma_val = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(r < st || l > dr) {
        return -1;
    }

    if(l <= st && dr <= r) {
        return aint[nod].best_ans;
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
}


int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d",&h[i],&a[i],&b[i]);
    }

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        int l,r;
        scanf("%d %d",&l,&r);
        queries[r].push_back({l,i});
    }

    for(int i = 1; i <= n; i++) {
        if(i + a[i] <= n) {
            add[i + a[i]].push_back(i);
        }
        if(i + b[i] + 1 <= n) {
            rem[i + b[i] + 1].push_back(i);
        }
    }

    init(1,1,n);

    for(int i = 1; i <= n; i++) {
        for(auto it:add[i]) {
            update(1,1,n,it,h[it]);
        }
        for(auto it:rem[i]) {
            update(1,1,n,it,NASPA);
        }
        if(max(i - b[i],1) <= i - a[i]) {
            update_best_ans(1,1,n,max(i - b[i],1),i - a[i],h[i]);
        }
        for(auto it:queries[i]) {
            ans[it.second] = query(1,1,n,it.first,i);
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
