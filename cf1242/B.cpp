#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;

int dsu[NMAX + 5];

int fi(int root) {
    if(dsu[root] == 0) {
        return root;
    }
    return dsu[root] = fi(dsu[root]);
}

bool uni(int x,int y) {
    x = fi(x);
    y = fi(y);

    if(x == y) {
        return false;
    }

    dsu[x] = y;

    return true;
}


int n,m;
vector<int> graph[NMAX + 5];
bool adj[NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int best = 1;

    for(int i = 2; i <= n; i++) {
        if(graph[i].size() < graph[best].size()) {
            best = i;
        }
    }


    vector<int> later;

    for(auto it:graph[best]) {
        adj[it] = true;
        later.push_back(it);
    }

    for(int i = 1; i <= n; i++) {
        if(adj[i] == false) {
            uni(i,best);
        }
    }

    for(auto it:later) {
        memset(adj,0,sizeof(adj));
        for(auto it2:graph[it]) {
            adj[it2] = true;
        }
        for(int i = 1; i <= n; i++) {
            if(adj[i] == false) {
                uni(i,it);
            }
        }
    }

    set<int> roots;

    for(int i = 1; i <= n; i++) {
        roots.insert(fi(i));
    }

    printf("%d\n",(int)roots.size() - 1);

    return 0;
}
