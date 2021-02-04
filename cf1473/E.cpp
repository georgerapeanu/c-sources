#include <bits/stdc++.h>

using namespace std;

struct edge_t{
    int to;
    int conf;
    int cost;
};

struct node_t{
    int nod;
    int conf;
    long long cost;

    bool operator < (const node_t &other)const{
        return this->cost > other.cost;
    }

};

const int NMAX = 2e5;

int n,m;

vector<edge_t> graph[NMAX + 5][4];

long long ans[NMAX + 5][4];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        for(int conf = 0; conf < 4;conf++){
            graph[a][conf].push_back({b,conf,w});
            graph[b][conf].push_back({a,conf,w});

            if((conf & 1) == 0){
                graph[a][conf].push_back({b,(conf | 1),2 * w});
                graph[b][conf].push_back({a,(conf | 1),2 * w});
            }
            if((conf & 2) == 0){
                graph[a][conf].push_back({b,(conf | 2),0});
                graph[b][conf].push_back({a,(conf | 2),0});
            }
            if((conf & 3) == 0){
                graph[a][conf].push_back({b,(conf | 3),w});
                graph[b][conf].push_back({a,(conf | 3),w});
            }
        }
    }

    for(int i = 1;i <= n;i++){
        for(int conf = 0;conf < 4;conf++){
            ans[i][conf] = 1e18;
        }
    }

    priority_queue<node_t> pq;

    ans[1][0] = 0;

    pq.push({1,0,0});

    while(pq.empty() == false){
        node_t nod = pq.top();
        pq.pop();
        if(ans[nod.nod][nod.conf] != nod.cost){
            continue;
        }

        for(auto it:graph[nod.nod][nod.conf]){
            if(ans[it.to][it.conf] > ans[nod.nod][nod.conf] + it.cost){
                ans[it.to][it.conf] = ans[nod.nod][nod.conf] + it.cost;
                pq.push({it.to,it.conf,ans[it.to][it.conf]});
            }
        }
    }

    for(int i = 2;i <= n;i++){
        printf("%lld ",ans[i][3]);
    }

    return 0;
}
