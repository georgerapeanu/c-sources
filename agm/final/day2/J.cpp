#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
const int inf = 1e9;
////////////////////////////////////////// BEGIN OF DINIC //////////////////////////////////////////
////////////////////////////////////// Note: 0-indexed vertices ////////////////////////////////////
struct Edge {
    int next;
    long long capacity;
    Edge(const int n, const long long c) : next(n), capacity(c) {}
};
class Dinic {
public:
    const int n;
    vector<int> idx;
    vector<int> dist;
public:
    vector<vector<int>> adj;
    vector<Edge> edges;
    Dinic(const int n)
        : n(n)
        , idx(n)
        , dist(n)
        , adj(n)
    {
    }
    void add_arc(const int u, const int v, const long long capacity) {
        if (u != v && capacity != 0) {
            const int uv = edges.size();
            edges.emplace_back(v, capacity);
            const int vu = edges.size();
            edges.emplace_back(u, 0);
            adj[u].push_back(uv);
            adj[v].push_back(vu);
        }
    }
    void add_edge(const int u, const int v, const long long capacity) {
        if (u != v && capacity != 0) {
            const int uv = edges.size();
            edges.emplace_back(v, capacity);
            const int vu = edges.size();
            edges.emplace_back(u, capacity);
            adj[u].push_back(uv);
            adj[v].push_back(vu);
        }
    }
    long long dfs(const int u, const int t, const long long delta) {
        if (delta == 0)
            return 0;
        if (u == t)
            return delta;
        int& i = idx[u];
        while (i >= 0) {
            const int uv = adj[u][i];
            const int v = edges[uv].next;
            if (dist[v] == dist[u]+1) {
                const long long bottleneck = dfs(v, t, min(delta, edges[uv].capacity));
                if (bottleneck > 0) {
                    const int vu = uv ^ 1;
                    edges[uv].capacity -= bottleneck;
                    edges[vu].capacity += bottleneck;
                    return bottleneck;
                }
            }
            --i;
        };
        return 0;
    }
    long long solve(const int s, const int t) {
        long long total_flow = 0;
        for (;;) {
            // Run a BFS
            queue<int> q;
            for (int v = 0; v < n; ++v)
                dist[v] = -1;
            dist[s] = 10;
            q.push(s);
            while (!q.empty()) {
                const int u = q.front();
                q.pop();
                for (const int i : adj[u]) {
                    const Edge& uv = edges[i];
                    const int v = uv.next;
                    if (uv.capacity > 0 && dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
            if (dist[t] == -1)
                break;
            // Find a blocking flow
            for (int v = 0; v < n; ++v)
                idx[v] = adj[v].size()-1;
            for (;;) {
                const long long flow = dfs(s, t, numeric_limits<long long>::max());
                if (flow == 0)
                    break;
                total_flow += inf - flow;
            }
        }
        return total_flow;
    }
};
////////////////////////////////////////// END OF DINIC //////////////////////////////////////////
////////////////////////////////////////// BEGIN OF L-R FLOWS WITH DINIC //////////////////////////////////////////
///////////////// Note: 0-indexed vertices /////////////////
///////////////// Warning: adding an edge with demand>capacity causes runtime error /////////////////
///////////////// Note: be careful with the return value -- if the total demand is 0 and compute() returns 0, there is nonetheless a feasible flow (namely, the empty flow) /////////////////
class LRDinic {
public:
    int n;
    vector<long long> from_source, to_sink, outgoing_capacity;
    long long total_demand;
public:
    Dinic dinic;
    LRDinic(const int n)
        : n(n)
        , from_source(n)
        , to_sink(n)
        , outgoing_capacity(n)
        , total_demand(0)
        , dinic(n+2)
    {
    }
    void add_arc(const int u, const int v, const long long demand, const long long capacity) {
        assert(capacity >= demand);
        if (u != v) {
            from_source[v] += demand;
            to_sink[u] += demand;
            dinic.add_arc(u, v, capacity-demand);
            total_demand += demand;
            outgoing_capacity[u] += capacity;
        }
    }
    long long compute(const int s, const int t) {
        // Add extra edges
        const int source = n;
        const int sink = n+1;
        int extra_edges = 0;
        for (int v = 0; v < n; ++v) {
            if (from_source[v] != 0) {
                ++extra_edges;
                dinic.add_arc(source, v, from_source[v]);
            }
            if (to_sink[v] != 0) {
                ++extra_edges;
                dinic.add_arc(v, sink, to_sink[v]);
            }
        }
        dinic.add_arc(t, s, std::numeric_limits<long long>::max());
        ++extra_edges;
        // Compute a feasible flow in G (by computing a saturating flow in G')
        long long flow_aux = dinic.solve(source, sink);
        if (flow_aux != total_demand)
            return 0;
        // Remove extra edges
        while (extra_edges--) {
            dinic.adj[dinic.edges.back().next].pop_back();
            dinic.edges.pop_back();
            dinic.adj[dinic.edges.back().next].pop_back();
            dinic.edges.pop_back();
        }
        // Extend the current flow to a maximum flow
        dinic.solve(s, t);
        long long flow = outgoing_capacity[s];
        for (const int idx : dinic.adj[s])
            flow -= dinic.edges[idx].capacity;
        return flow;
    }
};
class LRDinicRetrieval : public LRDinic {
private:
    vector<map<int, long long>> original_capacity;
public:
    LRDinicRetrieval(const int n)
        : LRDinic(n)
        , original_capacity(n)
    {
    }
    void add_arc(const int u, const int v, const long long demand, const long long capacity) {
        LRDinic::add_arc(u, v, demand, capacity);
        original_capacity[u][v] += capacity;
        original_capacity[v][u] -= capacity;
    }
    vector<map<int, long long>> retrieve_skew_flow() {
        vector<map<int, long long>> ans = original_capacity;
        for (int u = 0; u < n; ++u) {
            for (const int idx : dinic.adj[u]) {
                if ((idx&1) == 0) {
                    const Edge& e = dinic.edges[idx];
                    const int v = e.next;
                    ans[u][v] -= e.capacity;
                    ans[v][u] += e.capacity;
                }
            }
        }
        for (int u = 0; u < n; ++u) {
            for (auto it = ans[u].begin(), end=ans[u].end(); it != end; )
                if (it->second == 0)
                    it = ans[u].erase(it);
                else
                    ++it;
        }
        return ans;
    }
    vector<map<int, long long>> retrieve_gross_flow() {
        // Note: returns skew-symmetric flow
        vector<map<int, long long>> ans = original_capacity;
        for (int u = 0; u < n; ++u) {
            for (const int idx : dinic.adj[u]) {
                if ((idx&1) == 0) {
                    const Edge& e = dinic.edges[idx];
                    const int v = e.next;
                    ans[u][v] -= e.capacity;
                    ans[v][u] += e.capacity;
                }
            }
        }
        for (int u = 0; u < n; ++u) {
            for (auto it = ans[u].begin(), end=ans[u].end(); it != end; )
                if (it->second <= 0)
                    it = ans[u].erase(it);
                else
                    ++it;
        }
        return ans;
    }
};
////////////////////////////////////////// END OF L-R FLOWS WITH DINIC //////////////////////////////////////////


int n,m;
int x,y;

int main(){

  scanf("%d %d",&n,&m);
  scanf("%d %d",&x,&y);

  x--;
  y--;

  LRDinic solver(n);
  for(int i = 1;i <= m;i++){
    int u,v,d,c;
    scanf("%d %d %d %d",&u,&v,&d,&c);
    u--;
    v--;
    solver.add_arc(u,v,inf - c,inf - d);
  }

  printf("%lld\n",solver.compute(x,y));


  return 0;
}
