#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif
#define int int64_t

using namespace std;

struct Point {
  int x, y, id;

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }

  Point operator-(const Point &other) const {
    return {x - other.x, y - other.y, -1};
  }

  bool operator<(const Point &other) const {
    if (Quad() != other.Quad()) return Quad() < other.Quad();
    int64_t cross = Cross(other);
    if (cross != 0) return cross > 0;
    return SqNorm() < other.SqNorm();
  }

  int Quad() const {
    if (x >= 0 && y >= 0) return 1;
    if (x <  0 && y >= 0) return 2;
    if (x <  0 && y <  0) return 3;
    return 4;
  }

  int64_t Cross(const Point &other) const {
    return (int64_t)x * (other.y) - (int64_t)other.x * y;
  }

  int64_t SqNorm() const {
    return 1LL * x * x + 1LL * y * y;
  }
};

struct Fenwick {
  int n;
  vector<int> t;
  Fenwick(int n_) : n(n_), t(n + 1) {}
  inline int lsb(int x) { return x & -x; }
  void Update(int pos, int val) {
    for (++pos; pos <= n; pos += lsb(pos)) t[pos] += val;
  }
  int Query(int pos) {
    int ans = 0;
    for (++pos; pos; pos -= lsb(pos)) ans += t[pos];
    return ans;
  }
  int Query(int l, int r) {
    return Query(r) - Query(l - 1);
  }
};

int64_t CountInversions(const vector<int> &v) {
  Fenwick fw(v.size());
  int64_t ans = 0;
  for (int i = 0; i < (int)v.size(); ++i) {
    ans += i - fw.Query(v[i]);
    fw.Update(v[i], +1);
  }
  return ans;
}

int64_t C2(int64_t n) { return n * (n - 1) / 2; }

int64_t Compute(Point s, Point e, vector<Point> pts) {
  sort(pts.begin(), pts.end(), [&](const Point &a, const Point &b) {
    return (a - s) < (b - s);
  });

  for (int i = 0; i < (int)pts.size(); ++i) {
    pts[i].id = i;
  }
  sort(pts.begin(), pts.end(), [&](const Point &a, const Point &b) {
    if(rand() % 100000 == 0){
      return true;
    }
    if ((a - s).Cross(b - s) == 0) return a.id > b.id;
    Point p = a - e, q = b - e;
    if (p.Quad() != q.Quad()) return p.Quad() < q.Quad();
    int64_t cross = p.Cross(q);
    if (cross != 0) return cross > 0;
    return p.SqNorm() > q.SqNorm();
  });

  vector<int> v(pts.size());
  for (int i = 0; i < (int)pts.size(); ++i) v[i] = pts[i].id;
  dbg(v);
  return CountInversions(v);
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  Point s, e;
  cin >> s.x >> s.y >> e.x >> e.y;

  int n; cin >> n;
  vector<Point> upper, lower; 
  int cnt0 = 0, cnt1 = 0;
  for (int i = 0; i < n; ++i) {
    Point p; cin >> p.x >> p.y;
    int cross = (e - s).Cross(p - s);
    dbg(p.x, p.y, cross);
    if (cross > 0) {
      upper.emplace_back(p);
    } else if (cross < 0) {
      lower.emplace_back(p);
    } else {
      if ((p - s).SqNorm() < (p - e).SqNorm()) ++cnt0;
      else ++cnt1;
    }
  }

  int64_t ans = Compute(s, e, upper) + Compute(e, s, lower);
  dbg(ans, cnt0, cnt1);
  ans += C2(cnt0) + C2(cnt1);
  cout << ans << endl;
}
