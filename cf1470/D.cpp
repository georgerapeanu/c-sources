#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n,m;
vector<int> graph[NMAX + 5];
int color[NMAX + 5];
bool viz[NMAX + 5];

void dfs(int nod){
    viz[nod] = true;
    color[nod] = 1;

    for(auto it:graph[nod]){
        if(viz[it] == true && color[it] == 1){
            color[nod] = 0;
        }
    }

    for(auto it:graph[nod]){
        if(viz[it] == false){
            dfs(it);
        }
    }
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);
        for(int i = 1;i <= n;i++){
            viz[i] = false;
            color[i] = 0;
            graph[i].clear();
        }
        for(int i = 1;i <= m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dfs(1);

        bool bad = false;
        vector<int> teachers;

        for(int i = 1;i <= n;i++){
            if(viz[i] == false){
                bad = true;
                break;
            }
            if(color[i] == 1){
                teachers.push_back(i);
            }
        }

        if(bad == true){
            printf("NO\n");
        }else{
            printf("YES\n");
            printf("%d\n",(int)teachers.size());
            for(auto it:teachers){
                printf("%d ",it);
            }
            printf("\n");
        }
    }

    return 0;
}
