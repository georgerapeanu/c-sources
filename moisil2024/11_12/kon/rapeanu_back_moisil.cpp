#include <bits/stdc++.h>

using namespace std;

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

  queue<int> q;
  long long best_sum = 1e18;
  int best_conf = 0;
  for(int conf = 0; conf < (1 << n); conf++) {
    if(__builtin_popcount(conf) != k) continue;
    int visited = conf;
    
    long long worst_sum = 0;
    for(int i = 1; i <= n; i++) {
      if((visited >> (i - 1)) & 1) {
        continue;
      }
      long long sum = 0;
      q.push(i);
      visited |= (1 << (i - 1));

      while(!q.empty()) {
        int nod = q.front();
        q.pop();
        sum += power[nod];

        for(auto it:graph[nod]) {
          if((visited >> (it - 1)) & 1) {
            continue;
          }
          visited |= (1 << (it - 1));
          q.push(it);
        }
      }
      worst_sum = max(worst_sum, sum);
    }
    if(worst_sum < best_sum) {
      best_sum = worst_sum;
      best_conf = conf;
    }
  }
  
  printf("%lld\n", best_sum);
  for(int i = 0; i < n; i++) {
    if((best_conf >> i) & 1) {
      printf("%d ", i + 1);
    }
  }


  return 0;
}
