#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;

int n;
vector<int> graph[NMAX + 5];
vector<int> roots;

int dfs(int nod,int tata) {
    int sg = 1;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        int val = dfs(it,nod);
        sg = 1 + ((sg - 1) ^ val);
    }

    return sg;
}


int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int fa;
        scanf("%d",&fa);
        if(fa == 0) {
            roots.push_back(i);
        }
        else {
            graph[fa].push_back(i);
        }
    }

    int ans = 0;

    for(auto it:roots) {
        ans ^= dfs(it,0);
    }

    printf(ans != 0 ? "YES":"NO");

    return 0;
}
