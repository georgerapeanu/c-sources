#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

struct event_t{
  int x;
  int type;
  int id;
  bool operator < (event_t &other)const{
    if(x != other.x){
      return x < other.x;
    }
    return id < other.id;
  }
};


int n,m,l;
int x,y;
int ans[NMAX + 5];

int main(){

    scanf("%d %d %d",&n,&m,&l);    

    vector<event_t> events;

    for(int i = 1;i <= n;i++){
      scanf("%d %d",&x,&y);
      if(y <= l){
        events.push_back({x - (l - y),1,0});
        events.push_back({x + (l - y) + 1,-1,0});
      }
    }

    for(int i = 1;i <= m;i++){
      int x;
      scanf("%d",&x);
      events.push_back({x,0,i});
    }

    int active = 0;
    sort(events.begin(),events.end());

    for(auto it:events){
      active += it.type;
      ans[it.id] = active;
    }

    for(int i = 1;i <= m;i++){
      printf("%d\n",ans[i]);
    }

    return 0;
}
