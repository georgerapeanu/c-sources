#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int CMAX = 1e5;
const int QMAX = 1e5;

struct node_t {
    long long sum_leaves;
    int cnt_leaves;
    int cols;

    node_t() {
        sum_leaves = cnt_leaves = cols = 0;
    }

    node_t(int sum_leaves,int cnt_leaves) {
        this->sum_leaves = sum_leaves;
        this->cnt_leaves = cnt_leaves;
        this->cols = 0;
    }

} aint[4 * NMAX + 5];

int n,q;
vector<int> graph[NMAX + 5];
int lin[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int lin_id;

void predfs(int nod,int tata) {
    lin[++lin_id] = nod;
    fst[nod] = lin_id;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
    }
    lst[nod] = lin_id;
}

void merge_nodes(node_t &root,const node_t l,const node_t r) {
    root.sum_leaves = l.sum_leaves + r.sum_leaves + 1LL * (root.cnt_leaves) * ((long long)root.cols);
}

void build(int nod,int st,int dr) {
    aint[nod].cnt_leaves = dr - st + 1;
    if(st == dr) {
        aint[nod] = node_t(0,1);
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    merge_nodes(aint[nod],aint[nod * 2],aint[nod * 2 + 1]);
}

set<pair<int,int> > has_col[CMAX + 5];

void update(int nod,int st,int dr,int l,int r,int col,bool rem) {
    if(r < st || l > dr || (rem == false && has_col[col].count({st,dr}) > 0)) {
        return ;
    }
    if(l <= st && dr <= r) {
        if(rem == false) {
            aint[nod].cols++;

            set<pair<int,int> > :: iterator it = has_col[col].lower_bound({st,0});

            while(it != has_col[col].end() && it->second <= dr) {
                update(nod,st,dr,it->first,it->second,col,true);
                it = has_col[col].lower_bound({st,0});
            }

            has_col[col].insert({st,dr});
        }
        else {
            aint[nod].cols--;
            has_col[col].erase({st,dr});
        }
        if(st != dr) {
            merge_nodes(aint[nod],aint[nod * 2],aint[nod * 2 + 1]);
        }
        else {
            aint[nod].sum_leaves = aint[nod].cols;
        }
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,col,rem);
    update(nod * 2 + 1,mid + 1,dr,l,r,col,rem);
    merge_nodes(aint[nod],aint[nod * 2],aint[nod * 2 + 1]);
}

long long query(int nod,int st,int dr,int l,int r,int fa_cols) {
    if(r < st || l > dr) {
        return 0;
    }
    if(l <= st && dr <= r) {
        return 1LL * fa_cols * aint[nod].cnt_leaves + aint[nod].sum_leaves;
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r,fa_cols + (int)aint[nod].cols) +
           query(nod * 2 + 1,mid + 1,dr,l,r,fa_cols + (int)aint[nod].cols);
}
int main() {

    freopen("snowcow.in","r",stdin);
    freopen("snowcow.out","w",stdout);

    scanf("%d %d",&n,&q);

    for(int i = 1; i < n; i++) {
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    predfs(1,0);
    build(1,1,n);

    while(q--) {
        int t,x;
        scanf("%d %d",&t,&x);

        if(t == 1) {
            int c;
            scanf("%d",&c);
            update(1,1,n,fst[x],lst[x],c,false);
        }
        else {
            printf("%lld\n",query(1,1,n,fst[x],lst[x],0));
        }
    }


    return 0;
}
