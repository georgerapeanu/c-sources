#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;

int n;
vector<int> graph[NMAX + 5];
int weight[NMAX + 5];

int sum[NMAX + 5];
int last,delta;

void predfs(int nod,int tata){
    weight[nod] = 1;
    for(auto it:graph[nod]){
        if(it != tata){
            predfs(it,nod);
            weight[nod] += weight[it];
        } 
    }
}

int dfs(int nod,int tata){
    for(auto it:graph[nod]){
        if(it != tata && weight[it] * 2 > n){
            return dfs(it,nod);
        }
    }
    return nod;
}

void solve(int nod,int tata){
    sum[nod] = last;
    printf("%d %d %d\n",tata,nod,sum[nod] - sum[tata]);
    last += delta;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        solve(it,nod);
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    predfs(1,0);
    int centroid = dfs(1,0);
    predfs(centroid,0);

    sort(graph[centroid].begin(),graph[centroid].end(),[&](int a,int b){return weight[a] < weight[b];});

    int ind = (int)graph[centroid].size();
    int sum = 0;

    while(sum * 3 < (n - 1)){
        ind--;
        sum += weight[graph[centroid][ind]];
    }

    last = delta = 1;
    for(int i = 0;i < ind;i++){
        solve(graph[centroid][i],centroid);
    }
    last = delta = (n - 1) - sum;
    for(int i = ind;i < (int)graph[centroid].size();i++){
        solve(graph[centroid][i],centroid);
    }

    return 0;
}
