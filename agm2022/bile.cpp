#include <bits/stdc++.h>

using namespace std;


int main(){

  int n, r, t;

  scanf("%d %d %d", &n, &r, &t);

  vector<pair<long long, int> > balls(n, make_pair(0, 0));

  for(auto &ball:balls){
    scanf("%lld %d", &ball.first, &ball.second);
  }

  sort(balls.begin(), balls.end());
  
  for(int i = 0;i < n;i++){
    balls[i].first -= 2LL * r * i;
  }

  for(auto &it:balls){
    it.first += 1LL * it.second * t;
  }

  sort(balls.begin(), balls.end());

  for(int i = 0;i < n;i++){
    printf("%lld ", balls[i].first + 2LL * i * r);
  }

  return 0;
}
