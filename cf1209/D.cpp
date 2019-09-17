#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<int> graph[int(1e5) + 5];
int viz[int(1e5) + 5];

void dfs(int nod) {
    viz[nod] = true;
    for(auto it:graph[nod]) {
        if(viz[it] == false) {
            dfs(it);
        }
    }
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = m - n;

    for(int i = 1; i <= n; i++) {
        if(viz[i] == false) {
            ans++;
            dfs(i);
        }
    }

    printf("%d\n",ans);

    return 0;
}
