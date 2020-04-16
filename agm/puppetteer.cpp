#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500000;

long long t;
int n;
vector<int> graph[NMAX + 5];

bool active[NMAX + 5];
int val[NMAX + 5];

int weight[NMAX + 5];

vector<int> nodes;
int ans[NMAX + 5];
int cnt;

void add(int val) {
    active[val] = true;
    nodes.push_back(val);
    cnt++;
    if(active[val - 1]) {
        cnt--;
    }
    if(active[val + 1]) {
        cnt--;
    }
}

int query() {
    return cnt;
}

void clearAll() {
    for(auto it:nodes) {
        active[it] = false;
    }
    nodes.clear();
    cnt = 0;
}

void predfs(int nod,int tata) {
    weight[nod] = 1;

    for(auto it:graph[nod]) {
        if(it != tata) {
            predfs(it,nod);
            weight[nod] += weight[it];
        }
    }
}

void dfs2(int nod,int tata) {
    add(val[nod]);
    for(auto it:graph[nod]) {
        if(it != tata) {
            dfs2(it,nod);
        }
    }
}

void dfs(int nod,int tata,bool dump) {
    int bigChild = -1;

    for(auto it:graph[nod]) {
        if((bigChild == -1 || weight[it] > weight[bigChild]) && it != tata) {
            bigChild = it;
        }
    }

    for(auto it:graph[nod]) {
        if(it != tata && it != bigChild) {
            dfs(it,nod,true);
        }
    }

    if(bigChild != -1) {
        dfs(bigChild,nod,false);
    }

    for(auto it:graph[nod]) {
        if(it != tata && it != bigChild) {
            dfs2(it,nod);
        }
    }

    add(val[nod]);
    ans[nod] = query();
    if(dump) {
        clearAll();
    }
}

int main() {

    scanf("%lld",&t);

    while(t--) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&val[i]);
            graph[i].clear();
        }

        for(int i = 1; i < n; i++) {
            int x,y;
            scanf("%d %d",&x,&y);

            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        predfs(1,0);

        dfs(1,0,true);

        for(int i = 1; i <= n; i++) {
            printf("%d ",ans[i]);
        }

        printf("\n");
    }

    return 0;
}
