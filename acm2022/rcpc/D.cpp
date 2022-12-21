#include <bits/stdc++.h>

using namespace std;

//the size for a tree with N nodes and L leafs for F_K is 
//F_K= N + F_{K-1} * L - L = L * F_{K-1} + (N - L)
//F_0 = N
//F_K = L ^ K * N + (N - L) * (L ^ K - 1) / (L - 1)

const int NMAX = 1e5;
const long long LIM = (1LL << 30);

int main(){
  
  vector<vector<int> > euler_tours;
  vector<int> euler_tour;
  vector<int> euler_tour_pos;
  vector<vector<int> > rmq;
  vector<int> lg2;
  vector<int> lca_tour_pos;
  vector<int> lvl;
  vector<vector<int> > graph;

  function<void(int, int)> predfs = [&graph, &lvl, &euler_tour, &euler_tour_pos, &predfs](int nod, int tata){
    euler_tour.push_back(nod);
    euler_tour_pos[nod] = euler_tour.size() - 1;
    for(auto it:graph[nod]){
      if(it == tata){
        continue;
      }
      lvl[it] = 1 + lvl[nod];
      predfs(it, nod);
    }
  };

  function<void(int, int)> dfs_lca = [&graph, &rmq, &lca_tour_pos, &dfs_lca](int nod,int tata){
    rmq[0].push_back(nod);
    lca_tour_pos[rmq[0].back()] = rmq[0].size() - 1;
    for(auto it:graph[nod]){
      if(it == tata){
        continue;
      }
      dfs_lca(it, nod);
      rmq[0].push_back(nod);
    }
  };

  auto compose_nodes_lca = [&lvl](int x, int y){
    return lvl[x] < lvl[y] ? x:y;
  };

  auto make_lca = [&dfs_lca, &lg2, &rmq, &compose_nodes_lca, &lca_tour_pos, &graph](){
    lca_tour_pos = vector<int>(graph.size(), 0);
    rmq.push_back(vector<int>());
    dfs_lca(0, -1);
    lg2 = vector<int>(rmq[0].size() + 1);
    lg2[0] = -1;
    for(int i = 1;i < (int)lg2.size();i++){
      lg2[i] = 1 + lg2[i >> 1];
    }
    for(int h = 1;h <= lg2.back();h++){
      rmq.push_back(vector<int>(rmq[0].size()));
      for(int i = 0;i < (int)rmq[h].size();i++){
        rmq[h][i] = rmq[h - 1][i];
        if((1 << (h - 1) ) >= i){
          rmq[h][i] = compose_nodes_lca(rmq[h - 1][i], rmq[h - 1][i - (1 << (h - 1))]);
        }
      }
    }
    
  };

  auto lca = [&rmq, &lg2, &lca_tour_pos, &compose_nodes_lca](int x, int y){
    x = lca_tour_pos[x];
    y = lca_tour_pos[y];
    if(x > y){
      swap(x, y);
    }
    int h = lg2[y - x + 1];
    return compose_nodes_lca(rmq[h][y], rmq[h][x + (1 << h) - 1]);
  };

  auto compress = [](const vector<pair<int, int> > &v){
    vector<pair<int, int> > answer;
    for(const auto& it:v){
      if(answer.empty() || answer.back().first != it.first) {
        answer.push_back({it.first, 0});
      }
      answer.back().second += it.second;
    }
    return answer;
  };

  auto getPath = [&compress, &euler_tours = const_cast<const vector<vector<int> >&>(euler_tours)](int id, int k, int first_leaf_position){
    vector<pair<int, int> > answer;
    int skips = min(id / first_leaf_position, k - ((int)euler_tours.size() - 1));
    id -= skips * first_leaf_position;
    k -= skips;
    answer.push_back({first_leaf_position, skips});
    if(k > (int)euler_tours.size() - 1){
      answer.push_back({id, 1});
      return compress(answer);
    }
    for(int h = (int)euler_tours.size() - 1;h >= 0;h--){
      int pos = lower_bound(euler_tours[h].begin(), euler_tours[h].end(), id) - euler_tours[h].begin();
      assert(pos < (int)euler_tours[h].size());
      if(euler_tours[h][pos] == id){
        answer.push_back({pos, 1});
        break;
      }
      pos--;
      assert(0 <= pos);
      id -= euler_tours[h][pos];
      answer.push_back({pos, 1});
    }
    return compress(answer);
  };

  auto getPathLca = [&compress, &lca, &euler_tour = const_cast<const vector<int>&>(euler_tour), &euler_tour_pos = const_cast<const vector<int>&>(euler_tour_pos)](const vector<pair<int, int> > &x, const vector<pair<int, int> > &y){
    vector<pair<int, int> > answer;

    for(int i = 0;i < (int)min(x.size(), y.size());i++){
      if(x[i] != y[i]){
        if(x[i].first == y[i].first){
          answer.push_back({x[i].first, min(x[i].second, y[i].second)});     
          if(i + 1 >= (int)min(x.size(), y.size())){
            break;
          }
          int next_x = (x[i].second <= y[i].second ? x[i + 1].first:x[i].first);
          int next_y = (x[i].second >= y[i].second ? y[i + 1].first:y[i].first);
          answer.push_back({euler_tour_pos[lca(euler_tour[next_x], euler_tour[next_y])], 1});
        } else {
          answer.push_back({euler_tour_pos[lca(euler_tour[x[i].first], euler_tour[y[i].first])], 1});
        }
        break;
      }
      answer.push_back(x[i]);
    }
    return compress(answer);
  };

  auto getLevel = [&lvl = const_cast<const vector<int>&>(lvl), &euler_tour = const_cast<const vector<int>&>(euler_tour)](const vector<pair<int, int> > &path){
    int level = 0;
    for(const auto &it:path){
      level += it.second * lvl[euler_tour[it.first]];
    }
    return level;
  };


  auto init = [&euler_tour_pos, &lvl, &predfs, &graph, &make_lca, &euler_tours, &euler_tour](){
    euler_tour_pos = vector<int>(graph.size(), 0);
    lvl = vector<int>(graph.size(), 0);
    predfs(0, -1);
    make_lca();
    euler_tours.push_back(vector<int>(euler_tour.size(), 0));
    for(int i = 0;i < (int)euler_tours.size();i++){
      euler_tours[0][i] = 0;
    }
    long long last_size = (int)graph.size();
    for(int i = 1;last_size <= LIM;i++){
      euler_tours.push_back(vector<int>(euler_tour.size(), 0));
      long long next_id = 0;
      for(int j = 0;j < (int)euler_tours[i].size();j++){
        if(next_id > LIM){
          euler_tours[i].resize(j); 
          break;
        }
        euler_tours[i][j] = next_id;
        if(graph[euler_tour[j]].size() == 1 && euler_tour[j] != 0){ //leaf
          next_id += last_size; 
        } else {
          next_id += 1;
        }
      }
      last_size = next_id;
    }
  };

  int n;
  scanf("%d", &n);

  graph = vector<vector<int> >(n);

  for(int i = 1;i < n;i++){
    int parent;
    scanf("%d", &parent);
    graph[parent].push_back(i);
    graph[i].push_back(parent);
  }

  init();



  return 0;
}
