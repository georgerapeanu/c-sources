#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;

vector<long long> dijkstra(int source, const vector<vector<pair<int, long long> > > &graph){
  vector<long long> dist(graph.size(), inf);
  dist[source] = 0;
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;

  pq.push({dist[source], source});

  while(!pq.empty()){
    int nod = pq.top().second;
    long long cost = pq.top().first;
    pq.pop();
    if(cost != dist[nod]){
      continue;
    }
    for(auto it:graph[nod]){
      if(dist[it.first] > dist[nod] + it.second){
        dist[it.first] = dist[nod] + it.second;
        pq.push({dist[it.first], it.first});
      }
    }
  }

  return dist;
}

long long best_distance(const vector<long long> &dist_u, const vector<long long> &dist_v, vector<vector<pair<int, long long> > > &graph, const vector<pair<int,int> > &edges, int n){
//  for(auto it:dist_u)printf("%lld ", it);printf("\n");
//  for(auto it:dist_v)printf("%lld ", it);printf("\n");
  for(int i = 0;i < n;i++){
    graph[i].clear();
  }

  for(auto it:edges){
      graph[it.first].push_back({it.second, dist_v[it.second] - dist_v[it.first]});
  //    printf("edge from %d to %d with cost %lld\n", it.first, it.second, dist_v[it.second] - dist_v[it.first]);
  }
  
  if((int)graph.size() < n + 1){
    graph.push_back(vector<pair<int, long long> >());
  }else{
    graph[n].clear();
  }
  for(int i = 0;i < n;i++){
    graph[n].push_back({i, dist_u[i] + dist_v[i]});
  //  printf("edge from %d to %d with cost %lld\n", n, i, dist_u[i] + dist_v[i]);
  }
  //printf("\n");
  
  vector<long long> dist = dijkstra(n, graph); 

  long long best_dist = inf;

  for(int i = 0;i < n;i++){
    best_dist = min(best_dist, dist[i]);
  }
  return best_dist;
}

int main(){
  int n, m;
  int s, t;
  int u, v;

  scanf("%d %d", &n, &m);
  scanf("%d %d", &s, &t);
  scanf("%d %d", &u, &v);

  s--;
  v--;
  t--;
  u--;

  vector<vector<pair<int, long long> > > graph(n, vector<pair<int, long long> >());
  vector<pair<pair<int, int>,int> > edges;


  for(int i = 1;i <= m;i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    a--;
    b--;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
    edges.push_back({{a, b}, c});
  }

  vector<long long> dist_s = dijkstra(s, graph);
  vector<long long> dist_t = dijkstra(t, graph);
  
  vector<long long> dist_u = dijkstra(u, graph);
  vector<long long> dist_v = dijkstra(v, graph);

  vector<pair<int, int> > new_edges;

  for(auto it:edges){
    if(dist_t[it.first.first] + dist_s[it.first.second] + it.second == dist_s[t]){
      new_edges.push_back({it.first.second, it.first.first});
    }
    if(dist_s[it.first.first] + dist_t[it.first.second] + it.second == dist_s[t]){
      new_edges.push_back({it.first.first, it.first.second});
    }
  }

  long long fst = best_distance(dist_u, dist_v, graph, new_edges, n);
  long long snd = best_distance(dist_v, dist_u, graph, new_edges, n);
  long long trd = dist_u[v];
 
  printf("%lld\n", min(min(fst, snd), trd));
  
  return 0;
}
