#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn];
/// g[i] = lista de adiacenta a nodului i
bitset <maxn> viz;
vector <int> comp[maxn];
int cc;

void dfs(int node) {
    viz[node] = 1; /// il vizitez
    comp[cc].push_back(node);
    for(auto it : g[node])
        if(!viz[it])
            dfs(it);
    /*
    for(int i = 0 ; i < g[node].size() ; ++ i) {
        int newnode = g[node][i];
        if(!viz[newnode])
            dfs(newnode);
    }
    for(vector <int> :: iterator it = g[node].begin() ;
                        it != g[node].end(); ++ it)
        if(!viz[*it])
            dfs(*it);
    */
}

int main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1 ; i <= n ; ++ i)
        if(!viz[i]) { /// daca nu e vizitat
            ++ cc;
            dfs(i);
        }
    cout << cc << '\n';
  ///  for(int i = 1 ; i <= cc ; ++ i, cout << '\n')
     ///   for(auto it : comp[i])
     ///       cout << it << ' ';
    return 0;
}
