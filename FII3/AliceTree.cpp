#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n,x;
int gr[NMAX + 5];
int ord[NMAX + 5];
int father[NMAX + 5];
int fst_son[NMAX + 5];
int cnt_leafs[NMAX + 5];
int lvl[NMAX + 5];

bool locked[NMAX + 5];
int u,v;

int main() {

    scanf("%d %d",&n,&x);

    x++;

    if(n == 2) {
        printf("1 2\n");
        return 0;
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&gr[i]);
        ord[i] = i;
    }

    sort(ord + 1,ord + 1 + n,[&](int a,int b) {
        return gr[a] > gr[b];
    });

    vector<int> bfs = {ord[1]};
    int l = 2;

    lvl[ord[1]] = 1;

    for(int i = 0; i < (int)bfs.size(); i++) {
        for(int j = 1; j <= gr[bfs[i]] - (father[bfs[i]] != 0); j++) {
            father[ord[l]] = bfs[i];
            lvl[ord[l]] = 1 + lvl[bfs[i]];
            bfs.push_back(ord[l]);
            l++;
        }
    }

    for(int i = 2; i <= n; i++) {
        cnt_leafs[father[ord[i]]] += (gr[ord[i]] == 1);
        if(!fst_son[father[ord[i]]]) {
            fst_son[father[ord[i]]] = ord[i];
        }
    }

    locked[ord[1]] = true;

    for(u = ord[2]; fst_son[u]; u = fst_son[u]) {
        locked[u] = true;
    }

    for(v = ord[3]; fst_son[v]; v = fst_son[v]) {
        locked[v] = true;
    }

    vector<int> aval_alm_leaf;

    for(int i = 1; i <= n; i++) {
        if(!locked[i] && gr[i] > 1 && cnt_leafs[i] == gr[i] - (father[i] != 0)) {
            aval_alm_leaf.push_back(i);
        }
    }

    int lim = x - (lvl[u] + lvl[v] - 1);

    for(int i = 0; i < lim; i++) {
        swap(father[aval_alm_leaf[i]],father[u]);
        locked[aval_alm_leaf[i]] = true;
        cnt_leafs[father[u]]++;
        fst_son[father[u]] = u;
        if(!locked[father[u]] && cnt_leafs[father[u]] == gr[father[u]] - (father[father[u]] != 0)) {
            aval_alm_leaf.push_back(father[u]);
        }
        u = fst_son[aval_alm_leaf[i]];
    }

    for(int i = 1; i <= n; i++) {
        if(father[i]) {
            printf("%d %d\n",i,father[i]);
        }
    }

    return 0;
}

