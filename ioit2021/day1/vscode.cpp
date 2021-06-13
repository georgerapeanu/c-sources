#include <bits/stdc++.h>

using namespace std;

struct edge_t{
    int a,b;
    int t;
    int id;

    bool operator < (const edge_t &other)const{
        return t < other.t;
    }
};

class DSU{
    int n;
    vector<int> father;

public:

    DSU(int n){
        this->n = n;
        this->father = vector<int>(n + 1,0);
    }

    int find_root(int nod){
        if(father[nod] == 0){
            return nod;
        }
        return father[nod] = find_root(father[nod]);
    }

    bool unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        father[x] = y;

        return true;
    }
};

const int LGMAX = 20;
const int NMAX = 5e5;
const int SMAX = 5e5;

int n;
int s;
edge_t edges[NMAX + 5];
bool taken[NMAX + 5];

long long ans[NMAX + 5];

vector<pair<int,int> > graph[NMAX + 5];
int father[LGMAX + 1][NMAX + 5];
int _max[LGMAX + 1][NMAX + 5];
int lvl[NMAX + 5];

void dfs(int nod,int tata,int cost){
    lvl[nod] = 1 + lvl[tata];
    father[0][nod] = tata;
    _max[0][nod] = cost;
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        dfs(it.first,nod,it.second);
    }
}

void make_stramosi(){
    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= s;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
            _max[h][i] = max(_max[h - 1][i],_max[h - 1][father[h - 1][i]]);
        }
    }
}

int get_max(int a,int b){
    if(lvl[a] > lvl[b]){
        swap(a,b);
    }

    int ans = -1e9;

    for(int h = LGMAX;h >= 0;h--){
        if(((lvl[b] - lvl[a]) >> h) & 1){
            ans = max(ans,_max[h][b]);
            b = father[h][b];
        }
    }

    if(a == b){
        return ans;
    }

    for(int h = LGMAX;h >= 0;h--){
        if(father[h][a] != father[h][b]){
            ans = max(ans,_max[h][a]);
            ans = max(ans,_max[h][b]);
            a = father[h][a];
            b = father[h][b];
        }
    }

    ans = max(ans,_max[0][a]);
    ans = max(ans,_max[0][b]);

    return ans;
}

int main(){
      
    scanf("%d %d",&n,&s);
    
    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&edges[i].a,&edges[i].b,&edges[i].t);
        edges[i].id = i;
        edges[i].a++;
        edges[i].b++;
    }

    sort(edges + 1,edges + 1 + n);

    DSU solver(s);
    long long solver_ans = 0;

    for(int i = 1;i <= n;i++){
        if(solver.unite(edges[i].a,edges[i].b)){
            solver_ans += edges[i].t;
            graph[edges[i].a].push_back({edges[i].b,edges[i].t});
            graph[edges[i].b].push_back({edges[i].a,edges[i].t});
            taken[i] = true;
        }
    }

    dfs(1,0,0);
    make_stramosi();

    for(int i = 1;i <= n;i++){
        if(taken[i]){
            ans[edges[i].id] = solver_ans;
        }else{
            ans[edges[i].id] = solver_ans - get_max(edges[i].a,edges[i].b) + edges[i].t;
        }
    }


    for(int i = 1;i <= n;i++){
        printf("%lld\n",ans[i]);
    }

    return 0;
}
