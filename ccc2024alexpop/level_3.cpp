#include <bits/stdc++.h>

using namespace std;

void Move(char dir, int &x, int &y) {
  switch(dir) {
    case 'W':
      x -= 1;
      break;
    case 'A':
      y -= 1;
      break;
    case 'S':
      x += 1;
      break;
    case 'D':
      y += 1;
      break;
    default:
      throw runtime_error("Fuck");
  }
}

template<typename T>
bool self_min(T &a, const T &b) {
  if (a < b) return false;
  a = b;
  return true;
}

template<typename T>
bool self_max(T &a, const T &b) {
  if (a > b) return false;
  a = b;
  return true;
}

bool is_bad_cell(const vector<string> &a, int x, int y) {
  return x < 0 || y < 0 || x >= (int)a.size() || y >= (int)a[0].size() || a[x][y] == 'X';
}

pair<pair<int, int>, pair<int, int>> get_bb(string path) {
  int x = 0, y = 0;
  int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
  for (int i = 0;  i < (int)path.size(); ++i) {
    char c = path[i];
    Move(c, x, y);
    self_min(min_x, x);
    self_min(min_y, y);
    self_max(max_x, x);
    self_max(max_y, y);
  }
  return {{min_x, min_y}, {max_x, max_y}};
}

bool is_vaild_path(const vector<string> &a, string path) {
    auto bb = get_bb(path);
    int x = -bb.first.first, y = -bb.first.second;
    map<pair<int, int>, int> vis;
    vis[{x, y}] = -1;
    for (int i = 0; i < (int)path.size(); ++i) {
      char c = path[i];
      Move(c, x, y);
      if (is_bad_cell(a, x, y)) {
        cerr << "bad cell" << endl;
        cerr << "(" << x << ", " << y << ")\n";
        cerr << "i = " << i << endl;
        return false;
      }
      if (vis.count({x, y}) > 0) {
        cerr << "counted" << endl;
        return false;
      }
      vis[{x, y}] = i;
    }
    cerr << vis.size() << endl;
    return vis.size() == a.size() * a[0].size() - 1; 
}	


int main() {
  int n; cin >> n;
  for (int _ = 0; _ < n; ++_) {
    int m, n; cin >> m >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      assert((int)a[i].size() == m);
    }
    string s; cin >> s;
    cerr << s << ' ' << a[0] << endl;
    bool ans = is_vaild_path(a, s);
    cout << (ans ? "VALID" : "INVALID") << '\n';

    // cout << fq['W'] << ' ' << fq['D'] << ' ' << fq['S'] << ' ' << fq['A'] << '\n';
  }
  return 0;
}
