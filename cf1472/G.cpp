#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n,m;
vector<int> graph[NMAX + 5];
vector<int> d;

inline bool always_reachable(int s,int t){
    return true;
}

inline bool worse_reachable(int s,int t){
    return d[s] < d[t];
}

vector<int> bfs(vector<int> s,bool (*reachable)(int,int)){
    vector<int> q;
    vector<int> d(n + 1,0);
    
    for(auto it:s){
        q.push_back(it);
        d[it] = 1;
    }

    for(int i = 0;i < (int)q.size();i++){
        int nod = q[i];
        for(auto it:graph[nod]){
            if(reachable(nod,it) && d[it] == 0){
                d[it] = 1 + d[nod];
                q.push_back(it);
            }
        }
    }

    return d;
}

int ans[NMAX + 5];
int calc(int nod){
    if(ans[nod] == -1){
        ans[nod] = d[nod];

        for(auto it:graph[nod]){
            if(worse_reachable(nod,it)){
                ans[nod] = min(ans[nod],calc(it));
            }else{
                ans[nod] = min(ans[nod],d[it]);
            }
        }
    }
    return ans[nod];
}

int main(){
    
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            graph[i].clear();            
        }

        for(int i = 1;i <= m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            graph[u].push_back(v);
        }
        d = bfs({1},always_reachable);
        for(int i = 1;i <= n;i++){
            ans[i] = -1;
        }
        for(int i = 1;i <= n;i++){
            printf("%d ",calc(i) - 1);
        }
        printf("\n");
    }

    return 0;
}
