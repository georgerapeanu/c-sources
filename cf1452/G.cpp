#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n,k;
vector<int> graph[NMAX + 5];
int dist[NMAX + 5];
int lvl[NMAX + 5];

struct centroid_node_t{
    int father;
    vector<int> best_at_dist;
    map<int,int> dist;

    void process_updates(){
        for(int i = (int)best_at_dist.size() - 2;i >= 0;i--){
            best_at_dist[i] = max(best_at_dist[i],best_at_dist[i + 1]);
        }
    }

    void update(int d,int val){
        d = min(d,(int)best_at_dist.size() - 1);
   //     printf("deb %d\n",d);
        best_at_dist[d] = max(best_at_dist[d],val);
    }
    
    int query(int d){
        if(d >= (int)best_at_dist.size()){
            return 0;
        }
        return best_at_dist[d];
    }
};

centroid_node_t stuff[NMAX + 5];

bool in_centroid[NMAX + 5];
int w[NMAX + 5];

void predfs(int nod,int tata){
    lvl[nod] = 1 + lvl[tata];
    w[nod] = 1;
    for(auto it:graph[nod]){
        if(it == tata || in_centroid[it]){
            continue;
        }
        predfs(it,nod);
        w[nod] += w[it];
    }
}

void dfs2(int nod,int tata,int centroid){
    lvl[nod] = 1 + lvl[tata];
    stuff[centroid].dist[nod] = lvl[nod] - lvl[centroid];
    for(auto it:graph[nod]){
        if(it == tata || in_centroid[it]){
            continue;
        }
        dfs2(it,nod,centroid);
    }
}

void dfs(int nod,int tata){
    //printf("here %d %d\n",nod,tata);
    int real_father = tata;
    predfs(nod,tata);
    int total_w = w[nod];

    while(true){
        int big_child = -1;
        for(auto it:graph[nod]){
            if(it == tata || in_centroid[it]){
                continue;
            }
            if(big_child == -1 || w[it] > w[big_child]){
                big_child = it;
            }
        }
        if(big_child == -1 || w[big_child] * 2 <= total_w){
            break;
        }
        tata = nod;
        nod = big_child;
    }

    in_centroid[nod] = 1;
    stuff[nod].father = real_father;
    stuff[nod].best_at_dist = vector<int>(total_w + 1,0);
    //printf("update %d %d\n",nod,total_w + 1);

    for(auto it:graph[nod]){
        if(in_centroid[it]){
            continue;
        }
        dfs(it,nod);
    }
    in_centroid[nod] = 0;
    dfs2(nod,0,nod);
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        dist[i] = -1;
    }

    for(int i = 1;i < n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    scanf("%d",&k);

    queue<int> q;
    for(int i = 1;i <= k;i++){
        int nod;
        scanf("%d",&nod);
        dist[nod] = 0;
        q.push(nod);
    }

    while(!q.empty()){
        int nod = q.front();
        q.pop();
        for(auto it:graph[nod]){
            if(dist[it] == -1){
                dist[it] = dist[nod] + 1;
                q.push(it);
            }
        }
    }

    dfs(1,0);

    for(int i = 1;i <= n;i++){
        int nod = i;
        while(nod){
            if(stuff[nod].dist[i] < dist[i]){
                stuff[nod].update(dist[i] - stuff[nod].dist[i] - 1,dist[i]);
            }
            nod = stuff[nod].father;
        }
    }

    for(int i = 1;i <= n;i++){
        stuff[i].process_updates();
    }

    for(int i = 1;i <= n;i++){
        int ans = 0;
        int nod = i;

        while(nod){
            ans = max(ans,stuff[nod].query(stuff[nod].dist[i]));
            nod = stuff[nod].father;
        }
        printf("%d ",ans);
    }

    return 0;
}
