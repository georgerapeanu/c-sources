#include <bits/stdc++.h>

using namespace std;

//current sum, used kons
pair<long long, int> check(int nod, int tata, const vector<int> &power, const vector<vector<int> > &graph, vector<int> &solution, long long value, bool want_sol = false){
  long long current_sum = power[nod];
  int used_kons = 0;
  for(auto it:graph[nod]) {
    if(it == tata) {
      continue;
    }
    pair<long long, int> tmp = check(it, nod, power, graph, solution, value, want_sol);
    current_sum += tmp.first;
    used_kons += tmp.second;
  }
  if(current_sum > value){
    used_kons += 1;
    current_sum = 0;
    if(want_sol) {
      solution.push_back(nod);
    }
  }
  return make_pair(current_sum, used_kons);
}

int main() {

  freopen("arborele_frumos.in", "r", stdin);
  freopen("arborele_frumos.out", "w", stdout);

  int n, k;
  scanf("%d %d", &n, &k);

  vector<int> power(n + 1);
  vector<vector<int> > graph(n + 1);

  long long power_sum = 0;

  for(int i = 1;i <= n;i++) {
    scanf("%d", &power[i]);
    power_sum += power[i];
  }

  for(int i = 1;i < n;i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  long long low = -1;
  long long high = power_sum;

  vector<int> solution;
  solution.reserve(n);

  while(high - low > 1){
    long long mid = (low + high) / 2;
  
    if(check(1, 0, power, graph, solution, mid).second <= k){
      high = mid;
    } else {
      low = mid;
    }
  }

  solution.clear();
  check(1, 0, power, graph, solution, high, true);

  printf("%lld\n", high);

  vector<bool> taken(n + 1, false);
  for(const auto &it: solution) {
    taken[it] = true;
  }

  for(size_t i = 1; i < taken.size(); i++) {
    if(!taken[i] && (int)solution.size() < k) {
      solution.push_back(i);
    }
  }

  for(auto it:solution){
    printf("%d ", it);
  }

  return 0;
}
