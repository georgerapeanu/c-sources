#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

long long det(pair<int,int> a, pair<int,int> b,pair<int, int> c){
  return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(1, 100000,"n");
  inf.readEoln();

  for(int i = 0;i < n;i++){
    pair<int,int> points[4];
    for(int i = 0;i < 4;i++){
      points[i].first = inf.readInt(-4e5,4e5,"x");
      inf.readSpace();
      points[i].second = inf.readInt(-4e5,4e5,"y");
      inf.readEoln();
    }
    for(int i = 0;i < 4;i++){
      ensuref(det(points[i], points[(i + 1) & 3], points[(i + 2) & 3]) > 0, "Points starting from corner %d: (%d, %d) (%d, %d) (%d, %d) are not in strict trigonometric order", i, points[i].first, points[i].second, points[(i + 1) & 3].first, points[(i + 1) & 3].second, points[(i + 2) & 3].first, points[(i + 2) & 3].second);
    }
  }
  inf.readEof();

  return 0;
}

