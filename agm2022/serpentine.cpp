#include <bits/stdc++.h>
using namespace std;

struct circle_t{
  int x;
  int y;
  int r;
};

struct line_t{
  long double a;
  long double b;
  long double c;
};

struct point_t{
  long double x;
  long double y;
};
const int PARITY = 1;

/// this function returns a pair of lines, both interior tanges
/// the first one is from right to left;
/// the second one is from left to right
vector<line_t> get_line_between_circles(const circle_t &c1, const circle_t &c2){ 
  assert(c2.y > c1.y);
  long long x1 = c1.x;
  long long x2 = c2.x;
  long long y1 = c1.y;
  long long y2 = c2.y;
  long long r1 = c1.r;
  long long r2 = c2.r;

  long double sqrt_delta = 2 * (y2 - y1) * sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) - (r1 + r2) * (r1 + r2));

  long double a1 = (2 * (x1 - x2) * (r1 + r2) - sqrt_delta) / (2 * ((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2)));
  long double a2 = (2 * (x1 - x2) * (r1 + r2) + sqrt_delta) / (2 * ((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2)));
  long double b1 = (r1 + r2 - (x1 - x2) * a1) / (y1 - y2);
  long double b2 = (r1 + r2 - (x1 - x2) * a2) / (y1 - y2);
  long double _c1 = r1 - a1 * x1 - b1 * y1;
  long double _c2 = r1 - a2 * x1 - b2 * y1;

  line_t l1 = {a1, b1, _c1};
  line_t l2 = {a2, b2, _c2};

  return {l1, l2};
}

/// this function returns the intersection point between a tangent to the circle and the circle
point_t get_intersection_with_tangent(const circle_t &c, const line_t &l){
  if(l.a * c.x + l.b * c.y + l.c > 0){
    return {c.x - c.r * l.a, c.y - c.r * l.b};
  }else{
    return {c.x + c.r * l.a, c.y + c.r * l.b};
  }
}

long double get_distance_on_circle(const circle_t &c, const point_t &p1, const point_t &p2, int parity){
  long double theta1 = atan2(p1.y - c.y, p1.x - c.x);
  long double theta2 = atan2(p2.y - c.y, p2.x - c.x);
  //printf("%.2f %.2f\n", (double)theta1, (double)theta2);
  if((parity ^ PARITY) == 0){ /// around the right
    if(theta2 < theta1){
      theta2 += 2 * acos(-1);
    }
    //printf("going %.2f\n", (double)(theta2 - theta1));
    return (theta2 - theta1) * c.r;
  }else{
    if(theta2 > theta1){
      theta1 += 2 * acos(-1);
    }
    //printf("going %.2f\n", (double)(theta1 - theta2));
    return (theta1 - theta2) * c.r;
  }
}

long double get_distance(const point_t &p1, const point_t &p2){
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

///this assumes you start at the bottom of the first circle and end at the top of the last one
int main(){
  int n;
  int ys, yf; 
  scanf("%d %d %d", &n, &ys, &yf);
  vector<circle_t> circles(n, {0, 0, 0});

  for(auto &it:circles){
    scanf("%d %d %d", &it.x, &it.y, &it.r);
    it.y = ys - it.y;
  }
  yf = ys - yf;
  ys = 0;
  
  vector<line_t> lines;
  
  if(PARITY == 0){
    lines.push_back({1, 0, -(circles[0].x + circles[0].r)});
  }else{
    lines.push_back({1, 0, -(circles[0].x - circles[0].r)});
  }
  for(int i = 0;i + 1 < n;i++){
    lines.push_back(get_line_between_circles(circles[i], circles[i + 1])[(i & 1) ^ PARITY]); 
  //  printf("line between %d and %d is %.2f %.2f %.2f\n", i, i + 1, (double)lines.back().a, (double)lines.back().b, (double)lines.back().c);
  }
  if(((PARITY ^ (n - 1)) & 1) == 0){
    lines.push_back({1, 0, -(circles.back().x + circles.back().r)});
  }else{
    lines.push_back({1, 0, -(circles.back().x - circles.back().r)});
  }

  long double distance = 0;

  for(int i = 0;i < n;i++){
    point_t p1 = (get_intersection_with_tangent(circles[i], lines[i]));
    point_t p2 = (get_intersection_with_tangent(circles[i], lines[i + 1]));
    //printf("points on circle %d are %.2f %.2f and %.2f %.2f\n", i, (double)p1.x, (double)p1.y, (double)p2.x, (double)p2.y);
    distance += get_distance_on_circle(circles[i], p1, p2, i & 1);
  }

  for(int i = 0;i + 1 < n;i++){
    point_t p1 = get_intersection_with_tangent(circles[i], lines[i + 1]);
    point_t p2 = get_intersection_with_tangent(circles[i + 1], lines[i + 1]);
    //printf("distance between %.2f %.2f and %.2f %.2f is %.2f\n", (double)p1.x, (double)p1.y, (double)p2.x, (double)p2.y, (double)get_distance(p1, p2));
    distance += get_distance(p1, p2);
  }
  distance += get_intersection_with_tangent(circles[0], lines[0]).y - ys;
  distance += yf - get_intersection_with_tangent(circles.back(), lines.back()).y;

  printf("%.7f\n", (double)distance);

  return 0;  
}
