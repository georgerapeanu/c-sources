#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("task2.in","r");
FILE *g = fopen("task2.out","w");

const int NMAX = 1e6;
const long long VMAX = 1e9;
const long long inf = 1e17 + 5;

int n,q;
int v[NMAX + 5];

struct lazy_t {
    long long mi;
    long long ma;
    long long all;

    bool is_redundant() {
        return mi == 0 && ma == 0 && all == 0;
    }

    void make_redundant() {
        mi = 0;
        ma = 0;
        all = 0;
    }
};

struct node_t {
    vector<pair<long long,int> > v_mi;
    vector<pair<long long,int> > v_ma;
    long long sum;
    lazy_t lazy;


    node_t join(node_t &other) {
        node_t ans;
        ans.sum = this->sum + other.sum;
        ans.lazy.make_redundant();

        vector<pair<long long,int> > v_mi = this->v_mi;
        vector<pair<long long,int> > v_ma = this->v_ma;

        for(auto it:other.v_mi) {
            v_mi.push_back(it);
        }

        for(auto it:other.v_ma) {
            v_ma.push_back(it);
        }

        sort(v_mi.begin(),v_mi.end(),[](pair<long long,int> &a,pair<long long,int> &b) {
            if(a.first != b.first)return a.first < b.first;
            return a.second < b.second;
        });
        sort(v_ma.begin(),v_ma.end(),[](pair<long long,int> &a,pair<long long,int> &b) {
            if(a.first != b.first)return a.first > b.first;
            return a.second < b.second;
        });

        int l_mi = 0;
        for(int i = 1; i < (int)v_mi.size(); i++) {
            if(v_mi[l_mi].first != v_mi[i].first) {
                l_mi++;
                v_mi[l_mi] = v_mi[i];
            }
            else {
                v_mi[l_mi].second += v_mi[i].second;
            }
        }

        int l_ma = 0;
        for(int i = 1; i < (int)v_ma.size(); i++) {
            if(v_ma[l_ma].first != v_ma[i].first) {
                l_ma++;
                v_ma[l_ma] = v_ma[i];
            }
            else {
                v_ma[l_ma].second += v_ma[i].second;
            }
        }

        v_mi.resize(2);
        v_ma.resize(2);

        ans.v_mi = v_mi;
        ans.v_ma = v_ma;

        return ans;
    }
} aint[4 * NMAX + 5];

void build(int nod,int st,int dr,int v[]) {
    if(st == dr) {
        aint[nod].sum = v[st];
        aint[nod].v_mi = { {v[st],1},{inf,0} };
        aint[nod].v_ma = { {v[st],1}, {-inf,0} };
        aint[nod].lazy.make_redundant();
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid,v);
    build(nod * 2 + 1,mid + 1,dr,v);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}

void propag(int nod,int st,int dr) {
    if(aint[nod].lazy.is_redundant() || st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    aint[2 * nod].v_mi[0].first += aint[nod].lazy.all;
    aint[2 * nod].v_ma[0].first += aint[nod].lazy.all;
    aint[2 * nod].v_mi[1].first += aint[nod].lazy.all;
    aint[2 * nod].v_ma[1].first += aint[nod].lazy.all;
    aint[2 * nod].sum += aint[nod].lazy.all * (mid - st + 1);

    if(aint[2 * nod].v_mi[0].first <= aint[2 * nod + 1].v_mi[0].first) {
        aint[2 * nod].sum += aint[nod].lazy.mi * aint[2 * nod].v_mi[0].second;
        aint[2 * nod].v_mi[0].first += aint[nod].lazy.mi;
        aint[2 * nod].lazy.mi += aint[nod].lazy.mi;
    }

    if(aint[2 * nod].v_ma[0].first >= aint[2 * nod + 1].v_ma[0].first) {
        aint[2 * nod].v_ma[0].first += aint[nod].lazy.ma;
        aint[2 * nod].sum += aint[nod].lazy.ma * aint[2 * nod].v_ma[0].second;
        aint[2 * nod].lazy.ma += aint[nod].lazy.ma;
    }


    aint[2 * nod + 1].v_mi[0].first += aint[nod].lazy.all;
    aint[2 * nod + 1].v_ma[0].first += aint[nod].lazy.all;
    aint[2 * nod + 1].v_mi[1].first += aint[nod].lazy.all;
    aint[2 * nod + 1].v_ma[1].first += aint[nod].lazy.all;
    aint[2 * nod + 1].sum += aint[nod].lazy.all * (dr - mid);

    if(aint[2 * nod].v_mi[0].first >= aint[2 * nod + 1].v_mi[0].first) {
        aint[2 * nod + 1].sum += aint[nod].lazy.mi * aint[2 * nod + 1].v_mi[0].second;
        aint[2 * nod + 1].v_mi[0].first += aint[nod].lazy.mi;
        aint[2 * nod + 1].lazy.mi += aint[nod].lazy.mi;
    }

    if(aint[2 * nod].v_ma[0].first <= aint[2 * nod + 1].v_ma[0].first) {
        aint[2 * nod + 1].v_ma[0].first += aint[nod].lazy.ma;
        aint[2 * nod + 1].sum += aint[nod].lazy.ma * aint[2 * nod + 1].v_ma[0].second;
        aint[2 * nod + 1].lazy.ma += aint[nod].lazy.ma;
    }

    aint[2 * nod].lazy.all += aint[nod].lazy.all;
    aint[2 * nod + 1].lazy.all += aint[nod].lazy.all;

    aint[nod].lazy.make_redundant();
}

long long query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return 0;
    }

    if(S <= st && dr <= D) {
        return aint[nod].sum;
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D);
}

void update_add(int nod,int st,int dr,int S,int D,int x) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod].sum += 1LL * (dr - st + 1) * x;
        aint[nod].v_mi[0].first += x;
        aint[nod].v_mi[1].first += x;
        aint[nod].v_ma[0].first += x;
        aint[nod].v_ma[1].first += x;
        aint[nod].lazy.all = x;
        return ;
    }

    int mid = (st + dr) / 2;

    update_add(nod * 2,st,mid,S,D,x);
    update_add(nod * 2 + 1,mid + 1,dr,S,D,x);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}

void update_ma(int nod,int st,int dr,int S,int D,int x) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        if(x < aint[nod].v_mi[0].first) {
            return ;
        }
        if(x < aint[nod].v_mi[1].first) {
            aint[nod].lazy.mi = x - aint[nod].v_mi[0].first;
            aint[nod].v_mi[0].first += aint[nod].lazy.mi;
            aint[nod].sum += aint[nod].lazy.mi * aint[nod].v_mi[0].second;
            return;
        }
    }

    int mid = (st + dr) / 2;

    update_ma(nod * 2,st,mid,S,D,x);
    update_ma(nod * 2 + 1,mid + 1,dr,S,D,x);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}

void update_mi(int nod,int st,int dr,int S,int D,int x) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        if(x > aint[nod].v_ma[0].first) {
            return ;
        }
        if(x > aint[nod].v_ma[1].first) {
            aint[nod].lazy.ma = x - aint[nod].v_ma[0].first;
            aint[nod].v_ma[0].first += aint[nod].lazy.ma;
            aint[nod].sum += aint[nod].lazy.ma * aint[nod].v_ma[0].second;
            return;
        }
    }

    int mid = (st + dr) / 2;

    update_mi(nod * 2,st,mid,S,D,x);
    update_mi(nod * 2 + 1,mid + 1,dr,S,D,x);

    aint[nod] = aint[2 * nod].join(aint[2 * nod + 1]);
}
int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    build(1,1,n,v);

    while(q--) {
        int t,l,r;

        fscanf(f,"%d %d %d",&t,&l,&r);

        if(t == 1) {
            int x;
            fscanf(f,"%d",&x);
            update_ma(1,1,n,l,r,x);
        }
        else if(t == 2) {
            int x;
            fscanf(f,"%d",&x);
            update_mi(1,1,n,l,r,x);
        }
        else if(t == 3) {
            int x;
            fscanf(f,"%d",&x);
            update_add(1,1,n,l,r,x);
        }
        else {
            fprintf(g,"%lld\n",query(1,1,n,l,r));
        }
    }

    return 0;
}
