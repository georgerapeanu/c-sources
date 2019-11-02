#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 5e5;

int n,q;
int v[NMAX + 5];

int st[NMAX + 5],len;

vector<int> segments[NMAX + 5];
vector<pair<int,int> > queries[NMAX + 5];

int ans[NMAX + 5];

struct node_t {
    int ma_val;
    int lazy;
    int best_ans;
    int offset_min;
    int offset_max;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.ma_val = max(this->ma_val,other.ma_val);
        ans.lazy = 0;
        ans.offset_min = min(this->offset_min,other.offset_min);
        ans.offset_max = max(this->offset_max,other.offset_max);
        ans.best_ans = max(this->best_ans,other.best_ans);
        return ans;
    }

} aint[NMAX * 4 + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }
    aint[nod * 2].lazy = max(aint[nod * 2].lazy,aint[nod].lazy);
    aint[nod * 2 + 1].lazy = max(aint[nod * 2 + 1].lazy,aint[nod].lazy);
    aint[nod * 2].offset_min = max(aint[nod * 2].offset_min,aint[nod].lazy);
    aint[nod * 2].offset_max = max(aint[nod * 2].offset_max,aint[nod].lazy);
    aint[nod * 2 + 1].offset_min = max(aint[nod * 2 + 1].offset_min,aint[nod].lazy);
    aint[nod * 2 + 1].offset_max = max(aint[nod * 2 + 1].offset_min,aint[nod].lazy);
    aint[nod * 2].best_ans = aint[nod * 2].ma_val + aint[nod * 2].offset_max;
    aint[nod * 2 + 1].best_ans = aint[nod * 2 + 1].ma_val + aint[nod * 2 + 1].offset_max;
    aint[nod].lazy = 0;
}

void init(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod].ma_val = v[st];
        aint[nod].lazy = 0;
        aint[nod].best_ans = -1;
        aint[nod].offset_min = -(1 << 28);
        aint[nod].offset_max = -(1 << 28);
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int l,int r,int val) {
    propag(nod,st,dr);
    if(l > dr || r < st || aint[nod].offset_min >= val) {
        return ;
    }
    if(l <= st && dr <= r && aint[nod].offset_max <= val) {
        aint[nod].lazy = val;
        aint[nod].offset_min = max(aint[nod].offset_min,val);
        aint[nod].offset_max = max(aint[nod].offset_max,val);
        aint[nod].best_ans = aint[nod].ma_val + aint[nod].offset_max;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(l > dr || r < st) {
        return 0;
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
        scanf("%d",&v[i]);
    }

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        int l,r;
        scanf("%d %d",&l,&r);
        queries[l].push_back({r,i});
    }


    for(int i = 1; i <= n; i++) {
        while(len > 0 && v[st[len]] < v[i]) {
            segments[st[len]].push_back(i);
            len--;
        }
        if(len > 0) {
            segments[st[len]].push_back(i);
        }
        st[++len] = i;
    }

    init(1,1,n);

    for(int i = n; i; i--) {
        for(auto it:segments[i]) {
            if(2 * it - i <= n) {
                update(1,1,n,2 * it - i,n,v[i] + v[it]);
            }
        }
        for(auto it:queries[i]) {
            ans[it.second] = query(1,1,n,i,it.first);
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }


    return 0;
}

