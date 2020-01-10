#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2000;

int n;
int father[NMAX + 5];
vector<int> sons[NMAX + 5];
int weight[NMAX + 5];
bool active = 0;
int c[NMAX + 5];
int a[NMAX + 5],last;
int lvl[NMAX + 5];
bool used[NMAX + 5];

void dfs(int nod,int tata) {
    weight[nod] = 1;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:sons[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        weight[nod] += weight[it];
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&father[i],&c[i]);
        sons[father[i]].push_back(i);
    }

    dfs(0,0);

    for(int i = 1; i <= n; i++) {
        weight[i]--;
    }

    for(int i = 1; i <= n; i++) {
        if(weight[i] < c[i]) {
            printf("NO\n");
            return 0;
        }
    }

    for(int t = 1; t <= n; t++) {
        int bst_node = -1;

        for(int i = 1; i <= n; i++) {
            if(used[i] == 0 && c[i] == 0) {
                if(bst_node == -1 || (lvl[bst_node] > lvl[i])) {
                    bst_node = i;
                }
            }
        }

        int node = bst_node;
        a[node] = t;
        used[node] = true;

        while(node) {
            c[node]--;
            node = father[node];
        }
    }
    printf("YES\n");
    for(int i = 1; i <= n; i++)printf("%d ",a[i]);


    return 0;
}
