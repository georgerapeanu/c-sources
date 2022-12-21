#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif


using namespace std;

#define int int64_t

// https://github.com/georgerapeanu/kactl/blob/main/Alex/Point.h
struct Point {
  int x, y;
  Point (int x_, int y_) : x(x_), y(y_) {}
  friend ostream& operator<<(ostream &os, const Point &p) { return os << "(" << p.x << "," << p.y << ")"; }
  Point operator - (const Point &other) const {
    return {this->x - other.x, this->y - other.y};
  }
};


struct Line {
  int a, b, c;
  Line(Point p, Point q) : a(p.y - q.y), b(q.x - p.x), c(p.x * q.y - p.y * q.x) {}
};


int Det(const Point &a, const Point &b, const Point &c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}


vector<Point> ConvexHull(vector<Point> points) {
  for (auto &p : points) {
    if (p.x < points[0].x || (p.x == points[0].x && p.y < points[0].y)) {
      swap(points[0], p);
    }
  }

  sort(points.begin() + 1, points.end(), [&](const Point &a, const Point &b) {
    return Det(points[0], a, b) > 0;
  });

  vector<Point> stk = {points[0]};
  for (int i = 1; i < (int)points.size(); ++i) {
    while ((int)stk.size() >= 2 && Det(stk.end()[-2], stk.end()[-1], points[i]) <= 0) {
      stk.pop_back();
    }
    stk.emplace_back(points[i]);
  }
  return stk;
}


int64_t Dot(const Point &a, const Point &b) {
  return 1LL * a.x * b.x + 1LL * a.y * b.y;
}


long double Norm(const Point &a) {
  return sqrt(Dot(a, a));
}


long double Dist(const Point &a, const Line &l) {
  return (long double)abs(1LL * l.a * a.x + 1LL * l.b * a.y + l.c) / sqrt(1LL * l.a * l.a + 1LL * l.b * l.b);
}


bool SolveTest() {
  int n; 
  if (!(cin >> n)) {
    return false;
  }
  vector<Point> points(n, Point(0, 0));
  for (int i = 0; i < n; ++i) {
    cin >> points[i].x >> points[i].y;
  }

  points = ConvexHull(points);
  n = points.size();
  dbg(points);
  
  auto Next = [n](int i) { return i + 1 < n ? i + 1 : 0; };
  auto Prev = [n](int i) { return i > 0 ? i - 1 : n - 1; };

  auto MaximizeDot = [Next, points](int i, Point p, Point o) {
    while (Dot(points[Next(i)] - o, p) >= Dot(points[i] - o, p)) {
      i = Next(i);
    }
    return i;
  };

  auto MaximizeDotPrev = [Prev, points](int i, Point p, Point o) {
    while (Dot(points[Prev(i)] - o, p) >= Dot(points[i] - o, p)) {
      i = Prev(i);
    }
    return i;
  };

  auto MaximizeDist = [Next, points](int i, Point a, Point b) {
    while (abs(Det(a, b, points[Next(i)])) >= abs(Det(a, b, points[i]))) {
      i = Next(i);
    }
    return i;
  };

  int l = 0, u = 0, r = 0;
  {
    Line curr(points[0], points[1]);
    Point p = points[0], q = points[1];
    Point paral0(q.x - p.x, q.y - p.y);
    Point paral1(p.x - q.x, p.y - q.y);

    for (int i = 0; i < n; ++i) { 
      if (Dot(points[i] - q, paral1) > Dot(points[r] - q, paral1))
        r = i;
      if (Dot(points[i] - p, paral0) > Dot(points[l] - p, paral0))
        l = i;
      if (abs(Det(p, q, points[i])) > abs(Det(p, q, points[u])))
        u = i;
    }
  }

  long double ans = 1e18;
  for (int i = 0; i < n; ++i) {
    Point p = points[i], q = points[Next(i)];
    Line curr(p, q);
    Point paral0(q.x - p.x, q.y - p.y);
    Point paral1(p.x - q.x, p.y - q.y);
    
    l = MaximizeDot(l, paral0, p);
    l = MaximizeDotPrev(l, paral0, p);
    r = MaximizeDotPrev(r, paral1, q);
    r = MaximizeDot(r, paral1, p);
    u = MaximizeDist(u, p, q);

    long double h = Dist(points[u], curr);
    long double w = Dot(points[l], paral0) + Dot(points[r], paral1);
    long double len = Norm(paral0);
    long double result = 2 * h + 2 * w / len;
    ans = min(ans, result);
    dbg(i, l, r, h, w, len, result);
  }

  cout << fixed << setprecision(10) << ans << '\n';

  return true;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  while (SolveTest());
}

