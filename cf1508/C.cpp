#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int LGMAX = 18;

int n,m;

map<pair<int,int>,int> edges;

int d[NMAX + 5];

set<int> left_nodes;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> >> nodes;
int who[NMAX + 5];

vector<int> graph[NMAX + 5];

int cnt;

int lvl[NMAX + 5];
int last0[NMAX + 5];
int father[LGMAX + 1][NMAX + 5];

void dfs(int root){
    if(who[root] != 0 && d[root] == 0){
        last0[root] = root;
    }
    for(auto it:graph[root]){
        lvl[it] = 1 + lvl[root];
        last0[it] = last0[root];
        father[0][it] = root;
        dfs(it);
    }
}

int lca(int u,int v){
    if(lvl[u] > lvl[v]){
        swap(u,v);
    }

    for(int h = LGMAX;h >= 0;h--){
        if((lvl[v] - lvl[u]) >> h){
            v = father[h][v];
        }
    }

    if(u == v){
        return u; 
    }

    for(int h = LGMAX;h >= 0;h--){
        if(father[h][u] != father[h][v]){
            u = father[h][u];
            v = father[h][v];
        }
    }
    return father[0][u];
}

int main(){

    scanf("%d %d",&n,&m);

    int xo = 0;

    for(int i = 1;i <= m;i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        edges[{x,y}] = z;
        edges[{y,x}] = z;
        xo ^= z;
    }

    for(int i = 2;i <= n;i++){
        d[i] = 1 << 30;
        left_nodes.insert(i);
    }

    nodes.push({0,1});

    long long ans = 0;

    while(nodes.empty() == false){
        int node = nodes.top().second;
        int cost = nodes.top().first;
        nodes.pop();
        if(d[node] != cost){
            continue;
        }
        ans += cost;
        cnt += (cost == 0);
        if(left_nodes.count(node)){
            left_nodes.erase(node);
        }
        if(who[node]){
            graph[who[node]].push_back(node);
        }
        vector<int> to_erase;
        for(auto it:left_nodes){
            if(edges.count({node,it})){
                if(edges[{node,it}] < d[it]){
                    d[it] = edges[{node,it}];
                    nodes.push({d[it],it});
                    who[it] = node;
                }
            }else{
                d[it] = 0;
                who[it] = node;
                to_erase.push_back(it);
            }
        }
        for(auto it:to_erase){
            left_nodes.erase(it);
            nodes.push({d[it],it});
        }
    }

    if(1LL * n * (n - 1) / 2 - m > cnt){
        printf("%lld\n",ans);
        return 0;
    }

    dfs(1);

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    long long real_ans = ans + xo;

    for(auto it:edges){
        int u = it.first.first;
        int v = it.first.second;
        if(lvl[lca(u,v)] < max(lvl[last0[u]],lvl[last0[v]])){
            real_ans = min(real_ans,ans + it.second); 
        }
    }

    printf("%lld\n",real_ans);

    return 0;
}
