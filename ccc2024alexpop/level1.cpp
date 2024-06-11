#include <bits/stdc++.h>
#include <ostream>

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

char get_dir(pair<int, int> a, pair<int, int> b) {
  if (a.first == b.first) {
    if (a.second > b.second) {
      return 'A';
    } else if (a.second < b.second) {
      return 'D';
    } else {
      assert(false);
    }
  } else if (a.second == b.second) {
    if (a.first < b.first) {
      return 'S';
    } else if (a.first > b.first) {
      return 'W';
    } else {
      assert(false);
    }
  } else {
    assert(false);
  }
}

string get_path(vector<pair<int, int>> path) {
  string ans = "";
  for (int i = 1; i < (int)path.size(); ++i) {
    ans += get_dir(path[i - 1], path[i]);
  }
  return ans;
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
    // cerr << vis.size() << endl;
    return vis.size() == a.size() * a[0].size() - 1;
}

pair<int, int> find_tree(const vector<string> &a) {
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)a[i].size(); ++j) {
      if (a[i][j] == 'X') return {i, j};
    }
  }
  assert(false);
}

void move_left(pair<int, int> &cell, vector<pair<int, int>> &path, const function<bool(pair<int, int>)> &predicate) {
  while (!predicate(cell)) {
    cell.second -= 1;
    path.emplace_back(cell);
  }
}

void move_up(pair<int, int> &cell, vector<pair<int, int>> &path, const function<bool(pair<int, int>)> &predicate) {
  while (!predicate(cell)) {
    cell.first -= 1;
    path.emplace_back(cell);
  }
}

void move_right(pair<int, int> &cell, vector<pair<int, int>> &path, const function<bool(pair<int, int>)> &predicate) {
  while (!predicate(cell)) {
    cell.second += 1;
    path.emplace_back(cell);
  }
}

void move_down(pair<int, int> &cell, vector<pair<int, int>> &path, const function<bool(pair<int, int>)> &predicate) {
  while (!predicate(cell)) {
    cell.first += 1;
    path.emplace_back(cell);
  }
}

void step_right(pair<int, int> &cell, vector<pair<int, int>> &path) {
  cell.second += 1;
  path.emplace_back(cell);
}

void step_left(pair<int, int> &cell, vector<pair<int, int>> &path) {
  cell.second -= 1;
  path.emplace_back(cell);
}

void step_down(pair<int, int> &cell, vector<pair<int, int>> &path) {
  cell.first += 1;
  path.emplace_back(cell);
}

void step_up(pair<int, int> &cell, vector<pair<int, int>> &path) {
  cell.first -= 1;
  path.emplace_back(cell);
}

string get_path_odd_odd(const vector<string> &a) {
  int n = a.size(), m = a[0].size();
  assert(n % 2 == 1 && m % 2 == 1);
  auto tree = find_tree(a);

  assert(tree.first % 2 == tree.second % 2);
  if (tree.first % 2 == 0) { // case i)
    pair<int, int> cell = {tree.first, tree.second - 1};
    vector<pair<int, int>> path = {cell};
    move_left(cell, path, [&](auto c) {
      return c.second == 0;
    });
    while (cell.second < tree.second) {
      move_up(cell, path, [&](auto c) {
          return c.first == 0;
      });
      step_right(cell, path);
      move_down(cell, path, [&](auto c) {
        return c.first == tree.first - 1;
      });
      step_right(cell, path);
    }
    assert(cell.first == tree.first - 1 && cell.second == tree.second);
    cerr << "done 1.2" << endl;
    // terminam cadranul 2
    move_up(cell, path, [&](auto c) {
        return c.first == 0;
    });
    step_right(cell, path);
    assert(cell.first == 0 && cell.second == tree.second + 1);

    while (cell.first < tree.first) {
      move_right(cell, path, [&](auto c) {
        return c.second == m - 1;
      });
      step_down(cell, path);
      move_left(cell, path, [&](auto c) {
        return c.second == tree.second + 1;
      });
      step_down(cell, path);
    }
    assert(cell.first == tree.first && cell.second == tree.second + 1);
    cerr << "done 1.1" << endl;
    // terminam cadranul 1
    move_right(cell, path, [&](auto c) {
        return c.second == m - 1;
    });

    assert(cell.first == tree.first && cell.second == m - 1);

    while (cell.second > tree.second) {
      move_down(cell, path, [&](auto c) {
        return c.first == n - 1;
      });
      step_left(cell, path);
      move_up(cell, path, [&](auto c) {
        return c.first == tree.first + 1;
      });
      step_left(cell, path);
    }
    // terminam cadranul 4
    cerr << "done 1.4" << endl;
    assert(cell.first == tree.first + 1 && cell.second == tree.second);
    move_down(cell, path, [&](auto c) {
      return c.first == n - 1;
    });
    assert(cell.first == n - 1 && cell.second == tree.second);

    step_left(cell, path);
    while (cell.first > tree.first + 1) {
      // cerr << cell.first << ' ' << cell.second << ' ' << tree.first << ' ' << tree.second << endl;
      move_left(cell, path, [&](auto c) { return c.second == 0; });
      step_up(cell, path);
      move_right(cell, path, [&](auto c) {
        return c.second == tree.second - 1;
      });
      if (cell.first != tree.first + 1) {
        step_up(cell, path);
      }
    }
    cerr << "done 1.x" << endl;
    return get_path(path);
  } else {
    cerr << "second\n";
    pair<int, int> cell = {tree.first - 1, tree.second};
    vector<pair<int, int>> path = {cell};
    while (cell.first > 0) {
      step_up(cell, path);
      move_left(cell, path, [&](auto c) {
        return c.second == 0;
      });
      step_up(cell, path);
      move_right(cell, path, [&](auto c) {
        return c.second == tree.second;
      });
    }
    assert(cell.first == 0 && cell.second == tree.second);
    cerr << "2.1\n";
    step_right(cell, path);
    // done stanga sus
    move_down(cell, path, [&](auto c) {
      return c.first == tree.first;
    });

    while (cell.second < m - 1) {
      step_right(cell, path);
      move_up(cell, path, [&](auto c) {
        return c.first == 0;
      });
      step_right(cell, path);
      move_down(cell, path, [&](auto c) {
        return c.first == tree.first;
      });
    }

    assert(cell.first == tree.first && cell.second == m - 1);
    step_down(cell, path);
    cerr << "2.2\n";
    // done dr sus
    move_down(cell, path, [&](auto c) {
      return c.first == n - 1;
    });
    move_left(cell, path, [&](auto c) {
      return c.second == tree.second + 1;
    });
    cerr << "2.2.1\n";
    while (cell.first > tree.first + 1 && tree.second <= m - 2) {
      cerr << cell.first << ' ' << cell.second << ' ' << tree.first << ' ' << tree.second << ' ' << n << ' ' << m << endl;
      step_up(cell, path);
      cerr << "1kjklj \n";
      move_right(cell, path, [&](auto c) { return c.second >= m - 2; });
      cerr << "kjklj \n";
      step_up(cell, path);
      move_left(cell, path, [&](auto c) {
        return c.second == tree.second + 1;
      });
    }
    step_left(cell, path);
    cerr << "2.3" << '\n';
    assert(cell.first == tree.first + 1 && cell.second == tree.second);
    // done dreapta jos
    //
    move_down(cell, path, [&](auto c) {
      return c.first == n - 1;
    });
    step_left(cell, path);
    while (cell.second > 0) {
      move_up(cell, path, [&](auto c) {
        return c.first == tree.first;
      });
      step_left(cell, path);
      move_down(cell, path, [&](auto c) {
        return c.first == n - 1;
      });
      step_left(cell, path);
    }
    move_up(cell, path, [&](auto c) {
      return c.first == tree.first - 1; // -1 to go one row above to skip a step up after
    });
    move_right(cell, path, [&](auto c) {
      return c.second == tree.second - 1;
    });
    return get_path(path);
  }
}

string get_path_even(const vector<string> &a) {
  int n = a.size(), m = a[0].size();
  auto tree = find_tree(a);

  string path = "";
  vector<pair<int, int> > cells;
  if(n % 2 == 0) {
    cells.push_back({0, 1});
    for(int i = 0; i < n; i += 2) {
      for(int j = 2; j < m; j ++) {
        path += "D";
        cells.push_back({i, j});
      }
      path += "S";
      cells.push_back({i + 1, m - 1});
      for(int j = m - 2; j > 0; j --) {
        path += "A";
        cells.push_back({i + 1, j});
      }
      if(i + 2 < n) {
        path += "S";
        cells.push_back({i + 2, 1});
      }
    }
    path += "A";
    cells.push_back({n - 1, 0});
    for(int i = n - 2; i >= 0; i--) {
      path += "W";
      cells.push_back({i, 0});
    }
    path += "D";
  } else {
    cells.push_back({1, 0});
    for(int j = 0; j < m; j += 2) {
      for(int i = 2; i < n; i++) {
        path += "S";
        cells.push_back({i, j});
      }
      path += "D";
      cells.push_back({n - 1, j + 1});
      for(int i = n - 2; i > 0; i--){
        path += "W";
        cells.push_back({i, j + 1});
      }
      if(j + 2 < m) {
        path += "D";
        cells.push_back({1, j + 2});
      }
    }
    path += "W";
    cells.push_back({0, m - 1});
    for(int j = m - 2; j >= 0; j--) {
      path += "A";
      cells.push_back({0, j});
    }
    path += "S";
  }

  string actual_path = "";
  for(int i = 0; i < (int)cells.size(); i++) {
    if(cells[i] == tree) {
      for(int j = i + 1; j < (int)path.size(); j++) {
        actual_path += path[j];
      }
      for(int j = 0; j < i - 1; j++) {
        actual_path += path[j];
      }
    }
  }
 
  return actual_path;
}




int main() {
  int n; cin >> n;
  int max_n = 0, max_m = 0, max_nm = 0;
  for (int _ = 0; _ < n; ++_) {
    int m, n; cin >> m >> n;
    vector<string> a(n);
    self_max(max_n, n);
    self_max(max_m, m);
    self_max(max_nm, n * m);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      assert((int)a[i].size() == m);
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == 'X') {
          assert(n % 2 == 0 || m % 2 == 0 || (i + j) % 2 == (n + m) % 2);
        }
      }
    }

    if (n % 2 == 1 && m % 2 == 1) {
      auto ans = get_path_odd_odd(a);
      if (!is_vaild_path(a, ans)) {
        cout << ans << endl;
        cout << "WRONG\n";
      }
      cout << ans << '\n';
    } else {
      cout << get_path_even(a) << '\n';
    }

    // string s; cin >> s;
    // cerr << s << ' ' << a[0] << endl;
    // bool ans = is_vaild_path(a, s);
    // cout << (ans ? "VALID" : "INVALID") << '\n';

    // cout << fq['W'] << ' ' << fq['D'] << ' ' << fq['S'] << ' ' << fq['A'] << '\n';
  }
  return 0;
}
