#include <bits/stdc++.h>

using namespace std;

const int XMAX = 1e5;

struct point_t{
  int x, y;
};

struct line_t{
  int a, b;
  long long c;
};

int main(){

  vector<point_t> polygon;
  vector<line_t> lines;

  int x, y;

  while(cin >> x >> y){
    polygon.push_back({x, y});
  }
  
  for(int i = 0, ni = 1;i < (int)polygon.size();i++, ni = (ni + 1 == (int)polygon.size() ? 0:ni + 1)){
    lines.push_back({polygon[i].y - polygon[ni].y, polygon[ni].x - polygon[i].x, 1LL * polygon[i].x * polygon[ni].y - 1LL * polygon[i].y * polygon[ni].y });
  }

  for(int x = 0;x < XMAX;x++){
    vector<pair<int, int> > range;
    
  }

  return 0;
}
