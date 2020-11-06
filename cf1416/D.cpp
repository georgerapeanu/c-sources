#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 3e5;

struct dsu_t{
    int n;
    int dsu[NMAX + 5];
    int weight[NMAX +5];
    vector<set<int>> stuff;
    vector<pair<int,int> > op;

    dsu_t(){
    }

    dsu_t(vector<int> vals){
        this->n = (int)vals.size() - 1;
        stuff.resize(n + 1);
        for(int i = 1;i <= n;i++){
            dsu[i] = 0;
            weight[i] = 1;
            stuff[i].insert(vals[i]);
        }
    }

    int fi_root(int nod){
        if(dsu[nod] == 0){
            return nod;
        }
        return fi_root(dsu[nod]);
    }

    void unite(int x,int y){
        x = fi_root(x);
        y = fi_root(y);
        if(weight[x] > weight[y]){
            swap(x,y);
        }
        if(x == y){
            op.push_back({-1,-1});
            return ;
        }
        else{
            op.push_back({x,y}); 
            weight[y] += weight[x];
            dsu[x] = y;
            for(auto it:stuff[x]){
                stuff[y].insert(it);
            }
        }
    }

    void undo(){
        int x  = op.back().first;
        int y  = op.back().second;
        op.pop_back();
        
        if(x == -1){
            return ;
        }
        
        weight[y] -= weight[x];
        dsu[x] = 0;

        vector<int> tmp;
        for(auto it:stuff[x]){
            if(stuff[y].count(it)){
                stuff[y].erase(it);
            }
            else{
                tmp.push_back(it);
            }
        }

        for(auto it:tmp){
            stuff[x].erase(it);
        }
    }

    int query(int nod){
        nod = fi_root(nod);

        if(stuff[nod].empty()){
            return 0;
        }

        int ans = *stuff[nod].rbegin();
        stuff[nod].erase(ans);

        return ans;
    }
}dsu;

int n,m,q;
vector<int> vals = {0};
vector<pair<int,int> > queries;
vector<pair<int,int> > edges;

bool deleted[MMAX + 5];

int main(){

    scanf("%d %d %d",&n,&m,&q);

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        vals.push_back(val);
    }

    edges.push_back({0,0});

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        edges.push_back({x,y});
    }

    for(int i = 1;i <= q;i++){
        int t,a;
        scanf("%d %d",&t,&a);
        queries.push_back({t,a});
        if(t == 2){
            deleted[a] = true;
        }
    }

    dsu = dsu_t(vals);

    for(int i = 1;i <= m;i++){
        if(deleted[i] == false){
            dsu.unite(edges[i].first,edges[i].second);
        }
    }

    for(int i = q - 1;i >= 0;i--){
        int t = queries[i].first;
        int a = queries[i].second;
        if(t == 1){
            ;
        }
        else{
            dsu.unite(edges[a].first,edges[a].second);
        }
    }

    for(int i = 0;i < q;i++){
        int t = queries[i].first;
        int a = queries[i].second;
        if(t == 1){
            printf("%d\n",dsu.query(a));
        }
        else{
            dsu.undo();
        }
    }

    return 0;
}
