#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

struct query_t {
    int l,r;
    int w;
    int st,dr;
    int id;
};

struct node_t {
    int pref,segm,suff;
    bool all;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.pref = (this->all ? this->pref + other.pref:this->pref);
        ans.suff = (other.all ? other.suff + this->suff:other.suff);
        ans.segm = max(this->suff + other.pref,max(this->segm,other.segm));
        ans.all = (this->all & other.all);

        return ans;
    }
};

int n,q;
int h[NMAX + 5];
int ans[NMAX + 5];

vector<pair<int,int> > sorted_heights;
vector<query_t> v[NMAX + 5];

node_t aint[4 * NMAX + 5];

void init(int nod,int st,int dr) {
    aint[nod] = {0,0,0,0};
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return ;
    }
    if(st == dr) {
        aint[nod] = {val,val,val,val};
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);
    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

node_t query(int nod,int st,int dr,int S,int D) {
    if(D < st || S > dr) {
        return {0,0,0,1};
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D);
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&h[i]);
        sorted_heights.push_back({h[i],i});
    }

    sorted_heights.push_back({-1,0});

    sort(sorted_heights.begin(),sorted_heights.end());

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        query_t tmp;
        scanf("%d %d %d",&tmp.l,&tmp.r,&tmp.w);
        tmp.st = 0;
        tmp.dr = (int)sorted_heights.size();
        tmp.id = i;
        v[(tmp.st + tmp.dr) / 2].push_back(tmp);
    }

    while(true) {
        init(1,1,n);

        vector<pair<int,query_t> > to_ins;

        for(int i = n; i >= 1; i--) {
            update(1,1,n,sorted_heights[i].second,1);
            for(auto &it:v[i]) {
                if(query(1,1,n,it.l,it.r).segm >= it.w) {
                    it.st = (it.st + it.dr) / 2;
                }
                else {
                    it.dr = (it.st + it.dr) / 2;
                }
                if(it.dr - it.st == 1) {
                    ans[it.id] = sorted_heights[it.st].first;
                }
                else {
                    to_ins.push_back({(it.st + it.dr) / 2,it});
                }
            }
        }

        if(to_ins.empty()) {
            break;
        }

        for(int i = 1; i <= n; i++) {
            v[i].clear();
        }

        for(auto it:to_ins) {
            v[it.first].push_back(it.second);
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
