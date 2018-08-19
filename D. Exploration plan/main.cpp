#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2200;
const int INF = 1731315;
int start[1+MAX_N];
int cost[1+MAX_N][1+MAX_N];

vector<int> graph[1+MAX_N];
int l[1+MAX_N], r[1+MAX_N], last[1+MAX_N];
int op;

bool pairup(int nod) {
  if(op == last[nod])
    return false;
  last[nod] = op;

  for(auto it: graph[nod])
    if(r[it] == 0) {
      l[nod] = it;
      r[it] = nod;
      return true;
    }
  for(auto it: graph[nod])
    if(r[it] != 0 && pairup(r[it])) {
      l[nod] = it;
      r[it] = nod;
      return true;
    }
  return false;
}

bool test(int v, int e, int n, int k, int time) {
  int cuplaj = 0;
  bool cuplat = false;
  op = 1;
  for(int i = 1; i <= n; ++i) {
    last[i] = 0;
    graph[i].clear();
    for(int j = 1; j <= v; ++j) {
      if(cost[start[i]][j] <= time)
        graph[i].push_back(j);
      r[j] = 0;
    }
    l[i] = 0;
  }

  do {
    cuplat = false;
    for(int i = 1; i <= n; ++i)
      if(l[i] == 0 && pairup(i)) {
        cuplat = true;
        cuplaj++;
      }
    op++;
  } while(cuplat && cuplaj < k);
  return cuplaj >= k;
}

int main() {
  int v, e, n, k, a, b, t;
  scanf("%d%d%d%d", &v, &e, &n, &k);
  for(int i = 1; i <= n; ++i)
    scanf("%d", &start[i]);
  for(int l = 1; l <= v; ++l)
    for(int c = 1; c <= v; ++c)
      cost[l][c] = INF;
  for(int i = 1; i <= v; ++i)
    cost[i][i] = 0;
  for(int i = 0; i < e; ++i) {
    scanf("%d%d%d", &a, &b, &t);
    cost[a][b] = min(t, cost[a][b]);
    cost[b][a] = min(t, cost[b][a]);
  }

  for(int k = 1; k <= v; ++k)
    for(int i = 1; i <= v; ++i)
      for(int j = 1; j <= v; ++j)
        cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);

  int st = -1, dr = INF;
  while(dr - st > 1) {
    int mid = (st + dr) / 2;
    if(test(v, e, n, k, mid))
      dr = mid;
    else
      st = mid;
  }

  test(v, e, n, k, dr);

  if(dr == INF)
    printf("-1");
  else
    printf("%d", dr);
  return 0;
}
