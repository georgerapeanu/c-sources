#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn];
int dist[maxn], n, m, s;

void bfs(int st) {
    memset(dist, -1, sizeof(dist));
    dist[st] = 0;
    queue <int> q;
    q.push(st);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto it : g[node]) {
            if(dist[it] == -1) {
                dist[it] = dist[node] + 1;
                q.push(it);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i)
        cout << dist[i] << ' ';
}

int main() {
    freopen("bfs.in", "r", stdin);
    freopen("bfs.out", "w", stdout);

    cin.sync_with_stdio(false);
    cin >> n >> m >> s;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }
    bfs(s);
}
