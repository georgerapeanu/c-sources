#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;
vector<int> graph[500005];
int color[500005];

void solve(int st,int dr){
    //printf("deb %d %d\n",st,dr);
    if(dr - st <= 1){
        return ;
    }

    while(graph[st].empty() == false && (graph[st].back() >= dr || graph[st].back() <= st)){
        //printf("pop %d %d\n",st,graph[st].back());
        graph[st].pop_back();
    }
    
    if(graph[st].empty()){
        color[st + 1] = color[st];
        solve(st + 1,dr);
    }
    else{
        int lst = graph[st].back();
        color[lst] = color[st] ^ color[dr];
       // printf("goto %d\n",lst);
        solve(st,lst);
        solve(lst,dr);
    }
}

bool dfs(int nod){
    for(auto it:graph[nod]){
        if(color[it] == 0){
            color[it] = 3 - color[nod];
            if(dfs(it) == 0){
                return 0;
            }
        }
        else if(color[it] == color[nod]){
            return 0;
        }
    }
    return 1;
}

int main(){

    freopen("circle.in","r",stdin);
    freopen("circle.out","w",stdout);

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        sort(graph[i].begin(),graph[i].end());
    }

    bool ok = true;

    for(int i = 1;i <= n;i++){
        if(color[i] == 0){
            color[i] = 1;
            ok &= dfs(i);
        }
    }

    if(ok == 1){
        printf("%d\n",2);
        for(int i = 1;i <= n;i++){
            printf("%d ",color[i]);
        }
        return 0;
    }

    for(int i = 1;i <= n;i++){
        color[i] = 0;
    }

    color[1] = 1;
    color[n] = 2;
    solve(1,n);

    printf("%d\n",3);

    for(int i = 1;i <= n;i++){
        printf("%d ",color[i]);
    }

    return 0;
}
