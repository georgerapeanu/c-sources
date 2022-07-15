#include "testlib.h"
#include <bits/stdc++.h>
 
using namespace std;
 
using ld = long double;

long long det(pair<int,int> a, pair<int,int> b,pair<int, int> c){
  return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}
 
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int n = opt<int>("n");
    int mx = opt<int>("mx");
    int my = opt<int>("my");
	
	int x = rnd.next(-mx, mx);
	int y = rnd.next(-my, my);
	
	printf("%d\n", n);
	for (int i = 0; i < n ; ++i) {
        vector<pair<int, int> > points;

        points.push_back({x - rnd.next(1, mx), y + rnd.next(1, my)});
        points.push_back({x - rnd.next(1, mx), y - rnd.next(1, my)});
        points.push_back({0, 0});
        while(true){
          points[2] = {x + rnd.next(1, mx), y - rnd.next(1, my)};
          if(det(points[0], points[1], points[2]) > 0){
            break;
          }
        }
        points.push_back({0, 0});
        while(true){
          points[3] = {x + rnd.next(1, mx), y + rnd.next(1, my)};
          if(det(points[1], points[2], points[3]) > 0 && det(points[2], points[3], points[0]) > 0 && det(points[3], points[0], points[1]) > 0){
            break;
          }
        }
        for(auto it:points){
          printf("%d %d\n", it.first, it.second);
        }
	}
 
 
	return 0;
}

