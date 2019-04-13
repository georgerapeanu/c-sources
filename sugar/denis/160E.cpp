#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int NMAX = 4e5;

struct data_t {
    int t;
    int l,r;
    int id;
    bool is_query;

    bool operator < (const data_t &other)const {
        if(t != other.t) {
            return t < other.t;
        }
        return is_query > other.is_query;
    }
};

struct node_t {
    pair<int,int> max_left;
    set<pair<int,int> > s;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.max_left = max(this->max_left,other.max_left);
        ans.s.clear();
        return ans;
    }
};

int n,q;
int ans[NMAX + 5];
int pers_r[NMAX + 5];
vector<data_t> v;

vector<int> norm;
map<int,int> to_norm;

node_t aint[4 * NMAX + 5];

void init(int nod,int st,int dr) {
    aint[nod].max_left = {-1,0};
    aint[nod].s.insert({-1,0});
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void add(int nod,int st,int dr,int pos,pair<int,int> val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].s.insert(val);
        aint[nod].max_left = max(aint[nod].max_left,val);
        return ;
    }

    int mid = (st + dr) / 2;

    add(nod * 2,st,mid,pos,val);
    add(nod * 2 + 1,mid + 1,dr,pos,val);
    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void del(int nod,int st,int dr,int pos,pair<int,int> val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].s.erase(val);
        aint[nod].max_left = *aint[nod].s.rbegin();
        return ;
    }

    int mid = (st + dr) / 2;

    del(nod * 2,st,mid,pos,val);
    del(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

pair<int,int> query(int nod,int st,int dr,int S,int D) {
    if(D < st || S > dr) {
        return {-1,0};
    }

    if(S <= st && dr <= D) {
        return aint[nod].max_left;
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
}

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        int l,r,t;
        scanf("%d %d %d",&l,&r,&t);
        v.push_back({t,l,r,i,false});
        norm.push_back(l);
        norm.push_back(r);
    }


    for(int i = 1; i <= q; i++) {
        int l,r,t;
        scanf("%d %d %d",&l,&r,&t);
        v.push_back({t,l,r,i,true});
        norm.push_back(l);
        norm.push_back(r);
        pers_r[i] = r;
    }

    norm.push_back(-1);

    sort(norm.begin(),norm.end());
    norm.resize(unique(norm.begin(),norm.end()) - norm.begin());

    for(int i = 0; i < (int)norm.size(); i++) {
        to_norm[norm[i]] = i;
    }

    sort(v.begin(),v.end());

    init(1,1,(int)norm.size() - 1);

    for(auto it:v) {
        if(it.is_query) {
            add(1,1,(int)norm.size() - 1,to_norm[it.r], {it.l,it.id});
        }
        else {
            while(true) {
                pair<int,int> tmp = query(1,1,(int)norm.size() - 1,to_norm[it.l],to_norm[it.r]);
                if(tmp.first < it.l) {
                    break;
                }
                ans[tmp.second] = it.id;
                del(1,1,(int)norm.size() - 1,to_norm[pers_r[tmp.second]],tmp);
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d ",(ans[i] == 0 ? -1:ans[i]));
    }

    return 0;
}
