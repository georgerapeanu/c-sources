#include <bits/stdc++.h>

using namespace std;

//current sum, used kons
pair<long long, int> check(int nod, int tata, const vector<int> &power, const vector<vector<int> > &graph, long long value){
  long long current_sum = power[nod];
  int used_kons = 0;
  for(auto it:graph[nod]) {
    if(it == tata) {
      continue;
    }
    pair<long long, int> tmp = check(it, nod, power, graph, value);
    current_sum += tmp.first;
    used_kons += tmp.second;
  }
  if(current_sum > value){
    used_kons += 1;
    current_sum = 0;
  }
  return make_pair(current_sum, used_kons);
}

int main() {

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

  while(high - low > 1){
    long long mid = (low + high) / 2;
  
    if(check(1, 0, power, graph, mid).second <= k){
      high = mid;
    } else {
      low = mid;
    }
  }

  check(1, 0, power, graph, high);

  printf("%lld\n", high);
  for(int i = 1; i <= k; i++) {
    printf("%d ", i);
  }

  return 0;
}
