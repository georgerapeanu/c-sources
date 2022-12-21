#include <bits/stdc++.h>

using namespace std;

struct point_t{
  int x, y;
  
  int cross_product(const point_t &other)const{
    return this->x * other.y - this->y * other.x;
  }

  int dot_product(const point_t &other)const{
    return this->x * other.x + this->y * other.y;
  }

  point_t operator + (const point_t &other)const{
    point_t answer;
    answer.x = this->x + other.x;
    answer.y = this->y + other.y;
    return answer;
  }
  
  point_t operator - (const point_t &other)const{
    point_t answer;
    answer.x = this->x - other.x;
    answer.y = this->y - other.y;
    return answer;
  }

  long double dist(const point_t &other) const{
    return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y * other.y));
  }
  
  long double norm() const {
    return sqrt(x * x + y * y);
  }

  bool operator < (const point_t &other) const {
    if(this->x != other.x){
      return this->x < other.x;
    }
    return this->y < other.y;
  }
};

struct line_t{
  int a, b, c;
  
  static line_t build_from_points(point_t a, point_t b) {
    line_t answer;
    answer.a = a.y - b.y;
    answer.b = b.x - a.x;
    answer.c = a.x * b.y - a.y * b.x;
    return answer;
  }

  int eval(point_t p){
    return a * p.x + b * p.y + c;
  }
};

int solve(int n){
  
  vector<point_t> v(n);

  for(auto &it:v){
    cin >> it.x >>it.y;
  }

  sort(v.begin(), v.end());

  vector<point_t> convex_hull;

  for(const auto it:v){
    while((int)convex_hull.size() >= 2 && (convex_hull.back() - convex_hull[(int)convex_hull.size() - 2]).cross_product(it - convex_hull[(int)convex_hull.size() - 1]) <= 0) {
      convex_hull.pop_back();
    }
    convex_hull.push_back(it);
  }

  v.pop_back();
  reverse(v.begin(), v.end());
  
  for(const auto it:v){
    while((int)convex_hull.size() >= 2 && (convex_hull.back() - convex_hull[(int)convex_hull.size() - 2]).cross_product(it - convex_hull[(int)convex_hull.size() - 1]) < 0) {
      convex_hull.pop_back();
    }
    convex_hull.push_back(it);
  }

  convex_hull.pop_back();


  int leftmost = 0;
  int rightmost = 0;
  int upmost = 0;

  long double ans = 1e18;

  for(int i = 0;i < (int)convex_hull.size();i++){
    point_t current = convex_hull[i];
    point_t _next = convex_hull[(i + 1) % ((int)convex_hull.size())];
    point_t dir_v = (_next - current);
    while(abs(dir_v.cross_product(convex_hull[upmost] - convex_hull[i])) <= abs(dir_v.cross_product(convex_hull[(upmost + 1) % ((int)convex_hull.size())] - convex_hull[i]))) {
      upmost = (upmost + 1) % (int)convex_hull.size();
    }
    
    while(dir_v.dot_product(convex_hull[rightmost] - convex_hull[i]) <= dir_v.dot_product(convex_hull[(rightmost + 1) % ((int)convex_hull.size())] - convex_hull[i])) {
      rightmost = (rightmost + 1) % (int)convex_hull.size();
    }
    
    while(dir_v.dot_product(convex_hull[leftmost] - convex_hull[i]) >= dir_v.dot_product(convex_hull[(leftmost + 1) % ((int)convex_hull.size())] - convex_hull[i])) {
      leftmost = (leftmost + 1) % (int)convex_hull.size();
    }

    while(dir_v.dot_product(convex_hull[leftmost] - convex_hull[i]) >= dir_v.dot_product(convex_hull[((int)convex_hull.size() + leftmost - 1) % ((int)convex_hull.size())] - convex_hull[i])) {
      leftmost = ((int)convex_hull.size() + leftmost - 1) % (int)convex_hull.size();
    }

    long double width = (dir_v.dot_product(convex_hull[rightmost] - convex_hull[i]) - dir_v.dot_product(convex_hull[leftmost] - convex_hull[i])) / (dir_v.norm());
    long double height = abs(dir_v.cross_product(convex_hull[upmost] - convex_hull[i])) / dir_v.norm();
    ans = min(ans, 2 * width + 2 * height);
  }
  
  cout << fixed << setprecision(7) << ans << "\n";

  return 0;
}

int main(){
  int n;
  while(cin >> n){
    solve(n);
  }
}
