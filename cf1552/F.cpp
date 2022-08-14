#include <bits/stdc++.h>

using namespace std;

struct portal_t{
  int from;
  int to;
  int state;

  bool operator < (const portal_t &other) const {
    return this->from < other.from;
  }
};

const int MOD = 998244353;

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int main() {

  int n;
  scanf("%d", &n);

  vector<portal_t> portals;
  vector<pair<int, int> > coords;

  for(int i = 1;i <= n;i++){
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    portals.push_back({x, y, z});
    coords.push_back({x, -i});
    coords.push_back({y, +i});
  }
  
  coords.push_back({0, 0});

  sort(coords.begin(), coords.end());
  for(int i = 0;i < (int)coords.size();i++){
    if(coords[i].second < 0){
      portals[-coords[i].second - 1].from = i;
    }else if(coords[i].second > 0){
      portals[+coords[i].second - 1].to = i;
    }
  }

  vector<int> dp(coords.size(), 0);
  vector<int> to(coords.size(), -1);

  for(auto it:portals){
    to[it.from] = it.to;
  }

  for(int i = 1;i < (int)coords.size();i++){
    if(to[i - 1] == -1){
      dp[i] = sub(add(dp[i - 1], coords[i].first),  coords[i - 1].first);
    }else{
      dp[i] = add(add(dp[i - 1], sub(dp[i - 1], dp[to[i - 1]])), sub(coords[i].first, coords[i - 1].first));
    }
  }

  sort(portals.begin(), portals.end());

  int ans = 0;
  int last_index = 0;

  for(auto it:portals){
    if(it.state == 0){
      ans = add(ans, sub(coords[it.from].first, coords[last_index].first));
    }else{
      ans = add(add(ans, sub(coords[it.from].first, coords[last_index].first)), sub(dp[it.from], dp[it.to]));
    }
    last_index = it.from;
  }

  printf("%d\n", add(ans, 1));


  return 0;
}

