#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX_N = 500;
const int MAX_K = 6;
 
int fix[MAX_N + 5];
int f[MAX_N + 5][MAX_K + 5];
int t[MAX_N + 5];
int dp[MAX_N + 5][MAX_K * MAX_K + 5];
 
vector<int>G[MAX_N + 5];
vector<int>E[MAX_N + 5];
 
int l[MAX_N + 5], r[MAX_N + 5];
bool viz[MAX_N + 5];
int n1, m1;
 
int n, k;
 
bool match(int nod) {
  if (viz[nod])
    return false;
  viz[nod] = 1;
  for (auto it:E[nod]) {
    if (l[it] == 0) {
      r[nod] = it;
      l[it] = nod;
      return true;
    }
  }
  for (auto it:E[nod]) {
    if (!viz[l[it]] && match(l[it])) {
      r[nod] = it;
      l[it] = nod;
      return true;
    }
  }
  return false;
}
 
bool cuplaj() {
  bool ok1;
  do {
    ok1 = false;
    for (int i = 1; i <= n1; ++i)
      viz[i] = 0;
    for (int i = 1; i <= n1; ++i) {
      if (r[i] == 0 && match(i))
        ok1 = true;
    }
  } while (ok1);
  ok1 = 1;
  for (int i = 1; i <= n1; ++i) {
    if (!r[i])
      ok1 = 0;
    E[i].clear();
    r[i] = 0;
    viz[i] = 0;
  }
  for (int i = 1; i <= m1; ++i)
    l[i] = 0;
  return ok1;
}
int dfs(int node, int father) {
  t[node] = father;
  for (auto it:G[node])
    if (it != father)
      dfs(it, node);
}
 
void solve(int node, int father) {
  n1 = m1 = 0;
  for (auto it:G[node])
    if (it != father)
      solve(it, node);
  if (node != 1 && G[node].size() == 1) {
    int col = 0;
    for (int i = 1; i <= k; ++i)
      if (f[node][i]) {
        col = i;
        break;
      }
    if (fix[node]) {
      dp[node][(fix[node] - 1) * k + col - 1] = 1;
      return ;
    }
    for (int i = 1; i <= k; ++i)
      if (f[father][i])
        dp[node][(i - 1) * k + col - 1] = 1;
    return ;
  }
  if (node == 1) {
    dp[1][(fix[1] - 1) * k] = 1;
    for (auto it:G[1])
      if (!f[it][fix[1]])
        dp[1][(fix[1] - 1) * k] = 0;
    if (dp[1][(fix[1] - 1) * k]) {
      int nr = 0;
      for (int i = 1; i <= k; ++i) {
        if (f[node][i]) {
          int x = 0;
          for (auto it:G[node]) {
              x++;
            for (int j = 1; j <= f[node][i]; ++j)
              if (dp[it][(i - 1) * k + fix[node] - 1])
                E[x].push_back(nr + j);
          }
          nr += f[node][i];
        }
      }
      n1 = G[node].size();
      m1 = nr;
      dp[1][(fix[1] - 1) * k] = cuplaj();
    }
  } else {
    if (fix[node] && fix[father]) {
      int nr = 0;
      f[node][fix[father]]--;
      for (int i = 1; i <= k; ++i) {
        if (f[node][i]) {
          int x = 0;
          for (auto it:G[node]) {
            if (it != father)
              x++;
            for (int j = 1; j <= f[node][i]; ++j)
              if (it != father && dp[it][(i - 1) * k + fix[node] - 1])
                E[x].push_back(nr + j);
          }
          nr += f[node][i];
        }
      }
      n1 = G[node].size() - 1;
      m1 = nr;
      dp[node][(fix[node] - 1) * k + fix[father] - 1] = cuplaj();
      f[node][fix[father]]++;
    } else if (fix[node]) {
      for (int x = 1; x <= k; ++x) {
        if (f[node][x] && f[father][fix[node]]) {
          fix[father] = x;
          int nr = 0;
          f[node][fix[father]]--;
          for (int i = 1; i <= k; ++i) {
            if (f[node][i]) {
              int x = 0;
              for (auto it:G[node]) {
                if (it != father)
                  x++;
                for (int j = 1; j <= f[node][i]; ++j)
                  if (it != father && dp[it][(i - 1) * k + fix[node] - 1])
                    E[x].push_back(nr + j);
              }
              nr += f[node][i];
            }
          }
          n1 = G[node].size() - 1;
          m1 = nr;
          dp[node][(fix[node] - 1) * k + fix[father] - 1] = cuplaj();
          f[node][fix[father]]++;
          fix[father] = 0;
        }
      }
    } else if (fix[father]) {
      for (int x = 1; x <= k; ++x) {
        if (f[father][x] && f[node][fix[father]]) {
          fix[node] = x;
          int nr = 0;
          f[node][fix[father]]--;
          for (int i = 1; i <= k; ++i) {
            if (f[node][i]) {
              int x = 0;
              for (auto it:G[node]) {
                if (it != father)
                  x++;
                for (int j = 1; j <= f[node][i]; ++j)
                  if (it != father && dp[it][(i - 1) * k + fix[node] - 1])
                    E[x].push_back(nr + j);
              }
              nr += f[node][i];
            }
          }
          n1 = G[node].size() - 1;
          m1 = nr;
          dp[node][(fix[node] - 1) * k + fix[father] - 1] = cuplaj();
          f[node][fix[father]]++;
          fix[node] = 0;
        }
      }
    } else {
      for (int x = 1; x <= k; ++x) {
        for (int y = 1; y <= k; ++y) {
          if (f[node][y] && f[father][x]) {
            fix[node] = x;
            fix[father] = y;
            int nr = 0;
            f[node][fix[father]]--;
            for (int i = 1; i <= k; ++i) {
              if (f[node][i]) {
                int x = 0;
                for (auto it:G[node]) {
                  if (it != father)
                    x++;
                  for (int j = 1; j <= f[node][i]; ++j)
                    if (it != father && dp[it][(i - 1) * k + fix[node] - 1])
                      E[x].push_back(nr + j);
                }
                nr += f[node][i];
              }
            }
            n1 = G[node].size() - 1;
            m1 = nr;
            f[node][fix[father]]++;
            dp[node][(fix[node] - 1) * k + fix[father] - 1] = cuplaj();
            fix[node] = 0;
            fix[father] = 0;
          }
        }
      }
    }
  }
}
 
bool ok(int node, int col) {
  memset(dp, 0, sizeof(dp));
  fix[node] = col;
  solve(1, 0);
  return dp[1][(fix[1] - 1) * k];
}
 
int main() {
 
 freopen("design.in","r",stdin);
 freopen("design.ok","w",stdout);
 
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    for (int j = 1; j <= x; ++j) {
      int a;
      scanf("%d", &a);
      f[i][a]++;
    }
    for (int j = 1; j <= x; ++j) {
      int a;
      scanf("%d", &a);
      G[i].push_back(a);
    }
  }
 
  dfs(1, 0);
 
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= k; ++j)
      if (ok(i, j)) {
        fix[i] = j;
        printf("%d ", fix[i]);
        break;
      }
	  
 
  return 0;
}