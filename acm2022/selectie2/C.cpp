#include <bits/stdc++.h>

using namespace std;

struct edge_t{
  int from;
  int to;
  int from_id;
  int to_id;
  long double p;
};

int main(){

  int n, m;
  long long k;

  cin >> m >> n;
  cin >> k;

  // holds pairs of (time, id)
  vector<vector<pair<long long, int> > > node_stack(n); 

  // (time, node) -> ids;
  int last_id = 0;
  map<pair<long long, int>, int > to_id;

  auto get_id = [&to_id, &last_id](long long time, int city){
    if(to_id.count({time, city}) == 0){
      to_id[{time, city}] = last_id++;
    }
    return to_id[{time, city}];
  };

  vector<vector<edge_t> > graph(2 * m + 10, vector<edge_t>(0));
  vector<int> order;
  vector<int> in_degree(2 * m + 10, 0);

  for(int i = 0;i < m;i++){
    edge_t new_edge;
    long long from_time;
    long long to_time;
    cin >> new_edge.from;
    cin >> new_edge.to;
    cin >> from_time;
    cin >> to_time;
    cin >> new_edge.p;
    to_time++; ///because we cannot instantly switch bus

    new_edge.from_id = get_id(from_time, new_edge.from);
    new_edge.to_id = get_id(to_time, new_edge.to);
    node_stack[new_edge.from].push_back({from_time, new_edge.from_id});
    node_stack[new_edge.to].push_back({to_time, new_edge.to_id});

    graph[new_edge.from_id].push_back(new_edge);
    in_degree[new_edge.to_id]++;
    if(new_edge.from_id == new_edge.to_id)while(true);
     //cerr << "edge from " << new_edge.from_id << " to " << new_edge.to_id << " with " << new_edge.p << "\n";
  }
  int dest = get_id(k + 1, 1); // k + 1 because its alright if we arrive at the same time
  node_stack[1].push_back({k + 1, dest});
  int source = get_id(0, 0);
  node_stack[0].push_back({0, source});

  for(int i = 0;i < n;i++){
    sort(node_stack[i].begin(), node_stack[i].end());
    node_stack[i].resize(unique(node_stack[i].begin(), node_stack[i].end()) - node_stack[i].begin());

    for(int j = 0;j + 1 < (int)node_stack[i].size();j++){
      edge_t new_edge;
      new_edge.from = i;
      new_edge.to = i;
      new_edge.p = 1;
      new_edge.from_id = node_stack[i][j].second;
      new_edge.to_id = node_stack[i][j + 1].second;
      graph[new_edge.from_id].push_back(new_edge);
      in_degree[new_edge.to_id]++;
    if(new_edge.from_id == new_edge.to_id)while(true);
       //cerr << "edge from " << new_edge.from_id << " to " << new_edge.to_id << " with " << new_edge.p << "\n";
    }
  }

  for(int i = 0;i < last_id;i++){
    if(in_degree[i] == 0){
      order.push_back(i);
    }
  }

  for(int i = 0; i < (int)order.size();i++){
    for(auto it:graph[order[i]]) {
      in_degree[it.to_id]--;
      if(in_degree[it.to_id] == 0){
        order.push_back(it.to_id);
      }
    }
  }

  vector<long double> dp(order.size(), 0);
  dp[dest] = 1;

  // cerr << "source is " << source << "\n";
  // cerr << "dest is " << dest << "\n";

  for(int i = (int)order.size() - 1;i >= 0;i--){
    if(dest == order[i]){
      continue;
    }
    
    /* up edge, to dp[father]
     * side edge, with probability p and dp[side]
     * expected is p * dp[side] + (1- p) * dp[father]
     * we need to maximize p * (dp[side] - dp[father]) + dp[father]
     */

    long double father_dp = 0;

    for(const auto &edge:graph[order[i]]){
      if(edge.from == edge.to){
        father_dp = dp[edge.to_id];
        // cerr << "found father is " << edge.to_id << " " << edge.to << "\n";
        break;
      }
    }
   
    dp[order[i]] = father_dp;
    for(const auto &edge:graph[order[i]]){
      if(edge.from == edge.to){
        continue;
      }
      dp[edge.from_id] = max(dp[edge.from_id], edge.p * dp[edge.to_id] + (1 - edge.p) * father_dp);
    }
    // cerr << "dp for " << order[i] << " is " << dp[order[i]] << " father dp: " << father_dp <<  "\n";
  }

  cout << fixed << setprecision(10) <<dp[source];
   

  return 0;
}
