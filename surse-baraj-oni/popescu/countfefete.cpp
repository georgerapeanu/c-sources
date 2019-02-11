#include <bits/stdc++.h>
using namespace std;

int n;
const int MOD = 1e9 + 7;
int H[200005], TT[200005];
int v[200005];
int w[200005];
vector <int> V[200005];
inline void dfs(int nod, int t, int Lev){
    H[nod] = Lev;
    for(auto it : V[nod]){
        if(it == t) continue ;
        TT[it] = nod;
        dfs(it, nod, Lev + 1);
    }
}
inline int LCA(int x, int y, int &V){
    while(x != y){
        V = min(V, v[x]);
        V = min(V, v[y]);
        if(H[x] > H[y]) x = TT[x];
        else y = TT[y];
    }
    return x;
}
int Sol = 0;
inline void back(int k, int j, int X, int lca, int V){
    if(k > 1){
        Sol = Sol + (X ^ V);
        if(Sol >= MOD) Sol -= MOD;
    }
    for(int i = j + 1; i <= n ; ++i){
        w[k + 1] = i;
        int aux = lca;
        if(aux == 0) aux = i;
        int aux2 = min(V, v[i]);
        if(lca != 0)aux = LCA(i, lca, aux2);
        back(k + 1, i, X ^ v[i], aux, aux2);
    }
}
int main()
{
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n ; ++i)
        scanf("%d", &v[i]);
    int x, y;
    for(int i = 2; i <= n ; ++i){
        scanf("%d%d", &x, &y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dfs(1, 0, 0);
    back(0, 0, 0, 0, 2000000000);
    printf("%d", Sol);
    return 0;
}
