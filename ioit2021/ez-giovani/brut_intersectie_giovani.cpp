#include <bits/stdc++.h>

using namespace std;

typedef long double real_t;

const real_t eps = 1e-9;

struct point_t{
  real_t x;
  real_t y;

  point_t(){
    x = y = 0;
  }

  point_t(real_t x, real_t y){
    this->x = x;
    this->y = y;
  }
};

long double cross(const point_t &p_a, const point_t &p_b){
  return p_a.x * p_b.y - p_a.y * p_b.x;
}

struct line_t{
  real_t a;
  real_t b;
  real_t c;

  point_t p;
  point_t pq;

  line_t(){
    a = b = c = 0;
  }

  line_t(const point_t &p_a, const point_t &p_b){
    a = p_a.y - p_b.y;
    b = p_b.x - p_a.x;
    c = p_a.x * p_b.y - p_a.y * p_b.x;
    this->p = p_a;
    this->pq = point_t(p_b.x - p_a.x, p_b.y - p_a.y);
  }

  real_t eval(const point_t &p)const{
    return a * p.x + b * p.y + c;
  }

  point_t get_intersection(const line_t &other)const{
    ///a1 * x + b1 * y + c1 = 0
    ///a2 * x + b2 * y + c2 = 0
    ///(a2 * b1 - a1 * b2) * y + (a2 * c1 - a1 * c2) = 0
    ///(b2 * a1 - b1 * a2) * x + (b2 * c1 - b1 * c2) = 0
    /*
    real_t x = -(this->c * other.b - this->b * other.c) / (this->a * other.b - this->b * other.a);
    real_t y = -(this->a * other.c - this->c * other.a) / (this->a * other.b - this->b * other.a);
    */
 
    real_t alpha = cross(point_t(other.p.x - this->p.x, other.p.y - this->p.y), other.pq) / cross(this->pq, other.pq);

    real_t x = this->p.x + (this->pq.x) * alpha;
    real_t y = this->p.y + (this->pq.y) * alpha;

    return point_t(x, y);
  }
};

real_t det(const point_t &a, const point_t &b, const point_t &c){
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

struct halfplane_t{

  line_t split_line;

  halfplane_t(const point_t &p_a, const point_t &p_b){
    split_line = line_t(p_a, p_b);
  }

  bool is_in_halfplane(const point_t &p)const{
    return split_line.eval(p) > -eps;
  }
};

const real_t inf = 1e9;

class HalfplaneIntersection{
  vector<point_t> points;

  public:

  HalfplaneIntersection(){
    points.push_back(point_t(-inf,-inf));
    points.push_back(point_t(inf,-inf));
    points.push_back(point_t(inf,inf));
    points.push_back(point_t(-inf,inf));
  }

  void apply_halfplane(halfplane_t halfplane){
    vector<point_t> tmp_points;
    for(int i = 0;i < (int)points.size();i++){
      bool is_curr_ok = halfplane.is_in_halfplane(points[i]);
      bool is_nxt_ok = halfplane.is_in_halfplane(points[(i + 1) % points.size()]);
      if(is_curr_ok == 1 && is_nxt_ok == 1){
        tmp_points.push_back(points[i]);
      }else if(is_curr_ok == 1 && is_nxt_ok == 0){
        tmp_points.push_back(points[i]);
        tmp_points.push_back(line_t(points[i], points[(i + 1) % points.size()]).get_intersection(halfplane.split_line));
      }else if(is_curr_ok == 0 && is_nxt_ok == 1){
        tmp_points.push_back(line_t(points[i], points[(i + 1) % points.size()]).get_intersection(halfplane.split_line));
      }
    }
    points.clear();
    points = tmp_points;
  }

  real_t area(){
    real_t ans = 0;
    for(auto it:points)cerr << fixed << setprecision(10) << it.x << " " << it.y << endl;
    for(int i = 0;i < (int)points.size();i++){
      ans += det(points[0], points[i], points[(i + 1) % points.size()]);
    }
    if(ans < 0){
      ans *= -1;
    }
    return ans / 2;
  }
};


int main(){

  cin.sync_with_stdio(false);cin.tie(0);
  cout.sync_with_stdio(false);cout.tie(0);
  HalfplaneIntersection intersection;
  int n;
  cin >> n;

  while(n--){
    point_t points[4];
    for(int i = 0;i < 4;i++){
      cin >> points[i].x >> points[i].y;
    }
    for(int i = 0;i < 4;i++){
      intersection.apply_halfplane(halfplane_t(points[i], points[(i + 1) & 3]));
    }
  }

  cout << fixed << setprecision(10) <<  intersection.area() << endl;  

  return 0;
}
