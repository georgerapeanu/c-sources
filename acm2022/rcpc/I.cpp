#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e17;

struct order_t{
  int node;
  int start;
  int ready;
};

vector<long long> dijkstra(int source, const vector<vector<pair<int, int> > > &graph){
  vector<long long> dist(graph.size(), -1);
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int>> > pq; 

  dist[source] = 0;
  pq.push({0, source});

  while(!pq.empty()){
    long long d = pq.top().first;
    int node = pq.top().second;

    pq.pop();

    if(d != dist[node]){
        continue;
    }

    for(auto it:graph[node]){
      if(dist[it.first] == -1 || d + it.second < dist[it.first]){
        dist[it.first] = d + it.second;
        pq.push({dist[it.first], it.first});
      }
    }
  }
  return dist;
}

bool check(long long value, const vector<vector<long long> > &dists, const vector<order_t> &orders, const bool debug = false) {
  vector<long long> dp((int)orders.size(), inf);  
  dp[0] = 0;
  
  for(int i = 0;i < (int)orders.size();i++){
    long long leave_time = dp[i] + (i != 0 ? dists[orders[i].node][1]:0);
    long long last_leave_time = inf;
    long long running_time = 0;
    int running_node = 1;
    for(int j = i + 1;j < (int)orders.size();j++){
      // last_time + running_time + dist[running_node][orders[j].node] <= orders[j].start + value
      last_leave_time = min(last_leave_time, orders[j].start + value - dists[running_node][orders[j].node] - running_time);
      leave_time = max(leave_time, (long long)orders[j].ready);
      if(leave_time > last_leave_time){
        break;
      }
      running_time += dists[running_node][orders[j].node];
      running_node = orders[j].node;
      dp[j] = min(dp[j], leave_time + running_time); 
      if(debug)printf("%d updates %d with %lld\n", i ,j, running_time);
    }
  }
  return dp.back() != inf;
}


int main(){

  int n, m;

  scanf("%d %d", &n, &m); 
  vector<vector<pair<int ,int> > > graph(n + 1);

  for(int i = 0;i < m;i++){
    int a, b, d;
    scanf("%d %d %d", &a, &b, &d);

    graph[a].push_back({b, d});
    graph[b].push_back({a, d});
  }

  vector<vector<long long> > dists(n + 1);

  for(int i = 1;i <= n;i++){
    dists[i] = dijkstra(i, graph);
  }


  int q;

  scanf("%d", &q);

  vector<order_t> orders(q + 1);

  for(int i = 1;i <= q;i++){
    order_t order;
    scanf("%d %d %d", &order.start, &order.node, &order.ready);
    orders[i] = order;
  }
  
  long long left = -1;
  long long right = inf + 1;

  while(right - left > 1){
    long long mid = (left + right) >> 1;
    if(check(mid, dists, orders)){
      right = mid;
    }else{
      left = mid;
    }
  }

  //check(9, dists, orders, true);

  printf("%lld\n", right);
  
  return 0;
}
