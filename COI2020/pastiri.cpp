#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500005;

int n,k;
vector<int> graph[NMAX + 5];
queue<int> q;

int dist[NMAX + 5];

int viz[NMAX + 5];
int highest[NMAX + 5];
int lvl[NMAX + 5];

void predfs(int nod,int tata,int mx,int bst){
    lvl[nod] = 1 + lvl[tata];

    if(mx < lvl[nod] + dist[nod]){
        mx = lvl[nod] + dist[nod];
        bst = nod;
    }

    highest[nod] = bst;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod,mx,bst);
    }
}

void dfs_cover(int nod){
    viz[nod] = true;

    for(auto it:graph[nod]){
        if(viz[it] == 0 && dist[nod] == 1 + dist[it]){
            dfs_cover(it);
        }
    }
}


int main(){

    scanf("%d %d",&n,&k);

    for(int i = 1;i < n;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> sheeps;

    for(int i = 1;i <= k;i++){
        int nod;
        scanf("%d",&nod);
        q.push(nod);
        dist[nod] = 1;
        sheeps.push_back(nod);
    }

    while(q.empty() == false){
        int nod = q.front();
        q.pop();

        for(auto it:graph[nod]){
            if(dist[it] == 0){
                dist[it] = dist[nod] + 1;
                q.push(it);
            }
        }
    }

    predfs(1,0,-1,-1);

    sort(sheeps.begin(),sheeps.end(),[&](int a,int b){return lvl[a] > lvl[b];});

    vector<int> ans;

    for(auto it:sheeps){
        if(viz[it] == 0){
            dfs_cover(highest[it]);
            ans.push_back(highest[it]);
        }
    }

    sort(ans.begin(),ans.end());

    printf("%d\n",(int)ans.size());

    for(auto it:ans){
        printf("%d ",it);
    }

    return 0;
}
