#include <cstdio>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n,m;
int x,y;
int viz_a[NMAX + 5];
int viz_b[NMAX + 5];
vector<int> tr_graph[NMAX + 5];

void dfs(int nod,int viz[]) {
    viz[nod] = 1;

    for(auto it:tr_graph[nod]) {
        if(viz[it] == 0) {
            dfs(it,viz);
        }
    }
}

int main() {

    scanf("%d %d",&n,&m);
    scanf("%d %d",&x,&y);

    while(m--) {
        int x,y;
        scanf("%d %d",&x,&y);
        tr_graph[y].push_back(x);
    }

    dfs(x,viz_a);
    dfs(y,viz_b);

    int lca = -1;

    for(int i = 1; i <= n; i++) {
        if(viz_a[i] && viz_b[i]) {
            lca = i;
        }
    }

    for(int i = 1; i <= n; i++) {
        int ans = 2;

        if(lca != -1) {
            ans = min(ans,((viz_a[i] == 0) | (viz_b[i] == 0)));
        }
        else {
            ans = min(ans,2 - viz_a[i] - viz_b[i]);
        }
        printf("%d ",ans);
    }

    return 0;
}

