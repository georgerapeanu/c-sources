#include <bits/stdc++.h>

using namespace std;

struct point_t{
  int x,y;
  
  point_t(){
    x = y = 0;
  }

  point_t(int x,int y){
    this->x = x;
    this->y = y;
  }

  point_t operator + (const point_t &other)const{
    return point_t(this->x + other.x,this->y + other.y);
  }

  bool operator != (const point_t &other)const{
    return this->x != other.x || this->y != other.y;
  }

  bool operator == (const point_t &other)const{
    return this->x == other.x && this->y == other.y;
  }
};

int main(){

  int t;
  string s;
  cin >> t;

  vector<point_t> dir(256);

  dir['U'] = point_t(0,1);
  dir['L'] = point_t(-1,0);
  dir['R'] = point_t(1,0);
  dir['D'] = point_t(0,-1);

  while(t--){
    vector<point_t> points;

    cin >> s;

    points.push_back(point_t());

    for(auto it:s){
      points.push_back(points.back() + dir[it]);
    }

    point_t ans(0,0);
    for(auto it:points){
      if(it != point_t(0,0)){
        point_t obstacle = it;
        point_t current = point_t(0,0);

        for(auto it:s){
          if(current + dir[it] != obstacle){
            current = current + dir[it];
          }
        }
        if(current == point_t(0,0)){
          ans = obstacle;
          break;
        }
      }
    }
    printf("%d %d\n",ans.x,ans.y);
  }

  return 0;
}
