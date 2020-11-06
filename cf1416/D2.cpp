#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 3e5;
const int QMAX = 5e5;

class SegmentTree{
    int n;
    vector<int> aint;

    void update(int nod,int st,int dr,int pos,int val){
        if(dr < pos || st > pos){
            return ;
        }

        if(st == dr){
            aint[nod] = val;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
    }

    pair<int,int> query(int nod,int st,int dr,int l,int r){
        if(dr < l || st > r){
            return {-1,st};
        }

        if(st == dr){
            return {aint[nod],st};
        }

        int mid = (st + dr) / 2;

        if(l <= st && dr <= r){
            if(aint[nod * 2] > aint[nod * 2 + 1]){
                return query(nod * 2,st,mid,l,r);
            }
            else{
                return query(nod * 2 + 1,mid + 1,dr,l,r);
            }
        }

        return max(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
    }

public:
    SegmentTree(int n){
        aint = vector<int>(4 * n + 5,0);
        this->n = n;
    }

    void update(int pos,int val){
        update(1,1,n,pos,val);
    }

    pair<int,int> query(int l,int r){
        return query(1,1,n,l,r);
    }


};


struct dsu_t{
    vector<int> dsu;
    
    dsu_t(int n){
        dsu = vector<int>(n + 1,0);
    }

    int fi_root(int nod){
        if(dsu[nod] == 0){
            return nod;
        }
        return dsu[nod] = fi_root(dsu[nod]);
    }

    bool unite(int x,int y){
        x = fi_root(x);
        y = fi_root(y);
        if(x == y){
            return false;
        }
        dsu.push_back(0);
        dsu[x] = (int)dsu.size() - 1;
        dsu[y] = (int)dsu.size() - 1;
        return true;
    }
};

int n,m,q;
int p[NMAX + 5];
vector<pair<int,int> > edges = {{0,0}};
vector<pair<int,int> > queries = {{0,0}};

int deleted[MMAX + 5];

int root[QMAX + 5];

vector<int> graph[2 * NMAX + 5];
bool viz[2 * NMAX + 5];

int lft[2 * NMAX + 5];
int rgt[2 * NMAX + 5];
int lst = 0;

void dfs(int nod,SegmentTree &aint){
    viz[nod] = 1;
    if(graph[nod].empty()){
        lft[nod] = rgt[nod] = ++lst;
        aint.update(lft[nod],p[nod]);
    }
    else{
        lft[nod] = 1e9;
        rgt[nod] = 0;
        for(auto it:graph[nod]){
            dfs(it,aint);
            lft[nod] = min(lft[nod],lft[it]);
            rgt[nod] = max(rgt[nod],rgt[it]);
        }
    }
}

int main(){

    scanf("%d %d %d",&n,&m,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&p[i]);
    }

    edges = vector<pair<int,int> >(m + 1,{0,0});
    for(int i = 1;i <= m;i++){
        scanf("%d %d",&edges[i].first,&edges[i].second);
    }

    queries = vector<pair<int,int> >(q + 1,{0,0});
    for(int i = 1;i <= q;i++){
        scanf("%d %d",&queries[i].first,&queries[i].second);
        if(queries[i].first == 2){
            deleted[queries[i].second] = true;
        }
    }

    dsu_t dsu(n);

    for(int i = 1;i <= m;i++){
        if(deleted[i] == false){
            int x = dsu.fi_root(edges[i].first);
            int y = dsu.fi_root(edges[i].second);
            if(dsu.unite(x,y)){
                graph[dsu.fi_root(x)].push_back(x);
                graph[dsu.fi_root(x)].push_back(y);
            }
        }
    }

    for(int i = q;i;i--){
        if(queries[i].first == 1){
            root[i] = dsu.fi_root(queries[i].second);
        }
        else{
            int id = queries[i].second;
            int x = dsu.fi_root(edges[id].first);
            int y = dsu.fi_root(edges[id].second);

            if(dsu.unite(x,y)){
                graph[dsu.fi_root(x)].push_back(x);
                graph[dsu.fi_root(x)].push_back(y);
            }
        }
    }

    SegmentTree aint(n);

    for(int i = (int)dsu.dsu.size() - 1;i;i--){
        if(viz[i] == false){
            dfs(i,aint);
        }
    }

    for(int i = 1;i <= q;i++){
        if(queries[i].first == 1){
            pair<int,int> tmp = aint.query(lft[root[i]],rgt[root[i]]);
            printf("%d\n",tmp.first);
            aint.update(tmp.second,0);
        }
    }


    return 0;
}
