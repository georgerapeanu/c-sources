#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m; cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }

  int leaves = 0;
  int root = -1;
  for (int i = 0; i < n; ++i) {
    leaves += (int)g[i].size() == 1;
    if ((int)g[i].size() == 1) ++leaves;
    else root = i;
  }

  vector<int> depth(n), par(n, -1);
  function<void(int)> DFS = [&](int node) {
    for (int x : g[node]) {
      if (x == par[node]) continue;
      depth[x] = depth[node] + 1;
      par[x] = node;
      DFS(x);
    }
  };

  DFS(root);

  vector<bool> prot(n);

  auto Defender = [&]() {
    cout << "DEFEND" << endl;
    for (int i = 0; i < n; ++i) {
      if ((int)g[i].size() > 1) {
        cout << i << ' ';
        prot[i] = true;
        --m;
      }
    }

    int leaf = -1;
    for (int i = 0; i < n; ++i) {
      if ((int)g[i].size() == 1 && m > 0) {
        cout << i << ' ';
        prot[i] = true;
        leaf = i;
        --m;
      }
    }
    cout << endl;
    assert(leaf != -1);

    auto GetNode = [&]() {
      int node; cin >> node;
      if (node == -1) exit(0);
      return node - 1;
    };


    while (true) {
      int node = GetNode();
      if (prot[node]) {
        cout << 0 << endl; 
      } else {
        assert((int)g[node].size() == 1); 
        prot[leaf] = false;
        prot[node] = true;

        vector<int> path;
        while (depth[node] != depth[leaf]) {
          path.emplace_back(node);
          node = par[node];
        }
        vector<int> path2;
        while (node != leaf) {
          path.emplace_back(node);
          path2.emplace_back(leaf);  
          leaf = par[leaf];
          node = par[node];
        }
        path.emplace_back(node);
        reverse(path2.begin(), path2.end());
        for (int x : path2) path.emplace_back(x);
        cout << (int)path.size() - 1 << ' ';
        for (int i = 0; i + 1 < (int)path.size(); ++i) {
          cout << 1 + path[i] << ' ' << 1 + path[i + 1] << ' ';
        }
        cout << endl;
      }
    }
  };

  auto Attacker = [&]() {
    cout << "ATTACK" << endl;
  };

  int inner = n - leaves;
  if (m >= inner + 1) {
    Defender();
  } else {
    Attacker();
  }
}

