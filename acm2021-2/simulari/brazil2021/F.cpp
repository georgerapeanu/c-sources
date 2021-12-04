#include <bits/stdc++.h>

using namespace std;

struct point_t{
  int x,y;
  bool operator < (const point_t &other)const{
    if(y != other.y){
      return y < other.y;
    }
    return x < other.x;
  }

  point_t(){
    x = y = 0;
  }

  point_t(int x,int y){
    this->x = x;
    this->y = y;
  }
};

struct event_t{
  point_t curr;
  point_t ant;
  point_t nxt;
  bool type;///0 - for segment, 1 - query
  int id;
  
  bool operator < (const event_t &other)const{
    if(type != other.type){
      return type < other.type;
    }
    return this->curr < other.curr;
  }
};

struct segment_t{
  point_t low;
  point_t high;
  int id;
};

int n;


int main(){

  scanf("%d",&n);



  vector<event_t> events;
  for(int i = 1;i <= n;i++){
    int k;
    scanf("%d",&k);
    vector<point_t> poly(k,point_t());

    for(auto &it:poly){
      scanf("%d %d",&it.x,&it.y);
    }
    
    for(int j = 0;j < k;j++){
      event_t curr;
      curr.curr = poly[(j + 1) % k];
      curr.ant = poly[j];
      curr.nxt = poly[(j + 2) % k];
      curr.id = i;
      curr.type = 0;
      events.push_back(curr);
    }
    events.push_back({poly[0],poly[0],poly[0],1,i});
  }
  sort(events.begin(),events.end());
 
  int y;
  auto cmp = [&](const segment_t &a,const segment_t &b){
    if(a.low.y == a.high.y && b.low.y == b.high.y){
      return a.low.x < b.low.x;
    }
    return (__int128_t(y - a.low.y) * __int128_t(a.high.x - a.low.x) + __int128_t(a.low.x) * __int128_t(a.high.y - a.low.y)) * __int128_t(b.high.y - b.low.y) <= 
           (__int128_t(y - b.low.y) * __int128_t(b.high.x - b.low.x) + __int128_t(b.low.x) * __int128_t(b.high.y - b.low.y)) * __int128_t(a.high.y - a.low.y);
  };

  set<segment_t, decltype(cmp)> s(cmp);

  s.insert({point_t(-1e9 - 1,-1e9 -1),point_t(-1e9 -1,1e9 + 1),0});
  s.insert({point_t(1e9 + 1,-1e9 -1),point_t(1e9 +1,1e9 + 1),0});

  vector<pair<int,int> > edges;

  for(auto it:events){
    y = it.curr.y;
    printf("event %d (%d %d) %d\n",it.type,it.curr.x,it.curr.y,it.id);
    if(it.type == 0){
      /// V shape
      if(it.curr < it.ant && it.curr < it.nxt){
        segment_t query_boi = {it.curr,it.curr,0};
        printf("query %d %d\n",it.curr.x,it.curr.y);
        printf("bag pula %d\n",cmp(query_boi, *s.rbegin()));
        assert(s.lower_bound(query_boi) != s.end());
        segment_t insert_boi = {it.curr,it.ant,s.lower_bound(query_boi)->id};
        printf("insert (%d %d) (%d %d) %d\n",insert_boi.low.x,insert_boi.low.y,insert_boi.high.x,insert_boi.high.y,insert_boi.id);
        s.insert(insert_boi);
        printf("insert (%d %d) (%d %d) %d\n",insert_boi.low.x,insert_boi.low.y,insert_boi.high.x,insert_boi.high.y,insert_boi.id);
        insert_boi = {it.curr,it.nxt,it.id};
        s.insert(insert_boi);
      }
      /// \\ shape
      if(it.curr < it.ant && it.nxt < it.curr){
        segment_t query_boi = {it.nxt,it.curr,0};
        int id = s.lower_bound(query_boi)->id;
        s.erase(s.lower_bound(query_boi));
        segment_t insert_boi = {it.curr,it.ant,id};
        printf("insert (%d %d) (%d %d) %d\n",insert_boi.low.x,insert_boi.low.y,insert_boi.high.x,insert_boi.high.y,insert_boi.id);
        s.insert(insert_boi); 
      }
      /// // shape
      if(it.ant < it.curr && it.curr < it.nxt){
        segment_t query_boi = {it.ant,it.curr,0};
        int id = s.lower_bound(query_boi)->id;
        s.erase(s.lower_bound(query_boi));
        segment_t insert_boi = {it.curr,it.nxt,id};
        printf("insert (%d %d) (%d %d) %d\n",insert_boi.low.x,insert_boi.low.y,insert_boi.high.x,insert_boi.high.y,insert_boi.id);
        s.insert(insert_boi); 
      }
      /// ^ shape
      if(it.ant < it.curr && it.curr < it.nxt){
        segment_t query_boi = {it.ant,it.curr,0};
        s.erase(s.lower_bound(query_boi));
        query_boi = {it.nxt,it.curr,0};
        s.erase(s.lower_bound(query_boi));
      }
    }else if(it.type == 1){
      segment_t query_boi = {it.curr,it.curr,0};
      edges.push_back({s.lower_bound(query_boi)->id,it.id});
    }
  }

  for(auto it:edges){
    printf("%d %d\n",it.first,it.second);
  }
    
  return 0;
}
