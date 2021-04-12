#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];

vector<vector<int> > components;
int n,m;
int dfs_stack[NMAX + 5];
int dfs_len;
bool in_stack[NMAX + 5];
int id[NMAX + 5];
int low[NMAX + 5];
int last_id;

void dfs(int nod){
    dfs_stack[++dfs_len] = nod;
    id[nod] = low[nod] = ++last_id;
    in_stack[nod] = 1;

    for(auto it:graph[nod]){
        if(id[it] == 0){
            dfs(it);
        }
        if(in_stack[it]){
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == id[nod]){
        vector<int> component;
        while(dfs_stack[dfs_len] != nod){
            in_stack[dfs_stack[dfs_len]] = false;
            component.push_back(dfs_stack[dfs_len]);
            dfs_len--;
        }
        in_stack[dfs_stack[dfs_len]] = false;
        component.push_back(dfs_stack[dfs_len]);
        dfs_len--;
        sort(component.begin(),component.end());
        components.push_back(component);
    }
}

int main(){
    
    freopen("ctc.in","r",stdin);
    freopen("ctc.out","w",stdout);

    scanf("%d %d",&n,&m);

    while(m--){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
    }

    for(int i = 1;i <= n;i++){
        if(id[i] == 0){
            dfs(i);
        }
    }

    printf("%d\n",(int)components.size());

    for(auto it:components){
        for(auto it2:it){
            printf("%d ",it2);
        }
        printf("\n");
    }

    return 0;
}
