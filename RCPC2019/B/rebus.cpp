#include <fstream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

ifstream f("rebus.in");
ofstream g("rebus.out");

int tests;
int n;
string s[30];
string t;

class MaxFlowMinCost {
    int n;
    int cap[100][100];
    int flux[100][100];
    int cost[100][100];
    vector<int> graph[100];

    int old_d[100];
    int real_d[100];
    int dist[100];
    int father[100];

    int ans_flux;
    int fmin;
    int ans_cost;

public:

    MaxFlowMinCost(int n) {
        this->n = n;
        memset(cap,0,sizeof(cap));
        memset(cost,0,sizeof(cost));
        for(int i = 1; i <= n; i++) {
            graph[i].clear();
        }
        memset(old_d,0,sizeof(old_d));
        memset(real_d,0,sizeof(real_d));
        memset(dist,0,sizeof(dist));
        memset(father,0,sizeof(father));
        memset(flux,0,sizeof(flux));
        ans_flux = fmin = ans_cost = 0;
    }

    void add_edge(int u,int v,int w,int c) {
        if(cap[u][v] == 0) {
            cost[u][v] = c;
            cost[v][u] = -c;
        }
        cap[u][v] += w;
        cost[u][v] = min(cost[u][v],c);
        cost[v][u] = max(cost[v][u],-c);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool dijkstra(int s,int d) {
        for(int i = 1; i <= n; i++) {
            dist[i] = (1 << 28);
            real_d[i] = (1 << 28);
            father[i] = 0;
        }
        dist[s] = 0;
        real_d[s] = 0;

        priority_queue<pair<int,int>,vector<pair<int,int> > ,greater<pair<int,int> > > pq;

        pq.push({0,s});

        while(!pq.empty()) {
            pair<int,int> tmp = pq.top();
            pq.pop();
            if(dist[tmp.second] != tmp.first) {
                continue;
            }
            for(auto it:graph[tmp.second]) {
                if(flux[tmp.second][it] >= cap[tmp.second][it]) {
                    continue;
                }
                if(dist[it] > dist[tmp.second] + old_d[tmp.second] + cost[tmp.second][it] - old_d[it]) {
                    dist[it] = dist[tmp.second] + old_d[tmp.second] + cost[tmp.second][it] - old_d[it];
                    real_d[it] = real_d[tmp.second] + cost[tmp.second][it];
                    father[it] = tmp.second;
                    pq.push({dist[it],it});
                }
            }
        }

        memcpy(old_d,real_d,sizeof(real_d));

        if(dist[d] == (1 << 28)) {
            return false;
        }

        fmin = 1 << 28;

        for(int nod = d; nod != s; nod = father[nod]) {
            fmin = min(fmin,cap[father[nod]][nod] - flux[father[nod]][nod]);
        }

        ans_cost += fmin * real_d[d];
        ans_flux += fmin;

        for(int nod = d; nod != s; nod = father[nod]) {
            flux[father[nod]][nod] += fmin;
            flux[nod][father[nod]] -= fmin;
        }

        return true;
    }

    pair<int,int> solve(int s,int d) {
        for(; dijkstra(s,d););
        return {ans_flux,ans_cost};
    }
};

int main() {

    f >> tests;

    while(tests--) {
        f >> n;
        for(int i = 1; i <= n; i++) {
            f >> s[i];
        }
        f >> t;
        t = " " + t;

        int ans = (1 << 28);

        for(int mp = 0; mp <= 25; mp++) {
            MaxFlowMinCost a(n + 10);

            for(int i = 1; i <= n; i++) {
                a.add_edge(1,i + 1,1,0);
                a.add_edge(n + 1 + (t[i] - 'a' + 1),n + 10,1,0);
            }

            for(int i = 1; i <= n; i++) {
                for(int j = 0; j < (int)s[i].size(); j++) {
                    a.add_edge(i + 1,n + 1 + (s[i][j] - 'a' + 1),1,abs(j - mp));
                }
            }

            pair<int,int> tmp = a.solve(1,n + 10);
            if(tmp.first == n) {
                ans = min(ans,tmp.second);
            }
        }

        if(ans == (1 << 28)) {
            ans = -1;
        }

        g << ans << "\n";
    }

    f.close();
    g.close();

    return 0;
}
