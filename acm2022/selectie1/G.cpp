#include <bits/stdc++.h>

using namespace std;

const long long inf = 1LL << 62;

class LightSegmentTree{
  int n;
  vector<pair<long long, int>> aint;
public:

  LightSegmentTree(int n){
    this->n = n;
    this->aint = vector<pair<long long, int>>(2 * n, make_pair(inf, 0));
  }

  void update(int pos, long long value){
    //cerr << "update on " << this << " "  << pos << " with " << value << "\n";
    int b_pos = pos;
    for(pos += n;pos;pos >>= 1){
      aint[pos] = min(aint[pos], make_pair(value, b_pos));
    }
  }

  pair<long long, int> query(int l, int r){
    pair<long long, int> answer = make_pair(inf, 0);
    int b_l = l;
    int b_r = r;
    for(l += n, r += n;l < r;l >>=1, r>>= 1){
      if(l & 1){
        answer = min(answer, aint[l++]); 
      }
      if(r & 1){
        answer = min(answer, aint[--r]);
      }
    }
    //cerr << "query on " << this << " " << b_l << " " << b_r << " is " << answer.first << " " << answer.second << "\n";
    return answer;
  }
};


int main(){

  long long l, a, b, t, r;

  cin >> l >> a >> b >> t >> r;

  int n;

  cin >> n;
  vector<long long> v(n + 1, 0);

  for(int i = 1;i <= n;i++){
    cin >> v[i];
  }
  
  v.push_back(l);
  n++;

  vector<pair<long long, int>> dp(n + 1, make_pair(0, 0));
  
  dp[n] = make_pair(0, -1);

  LightSegmentTree aint1(n + 1), aint2(n + 1);

  int first_point = n;
  int second_point = n;

  pair<long long, int> tmp;
  for(int i = n;i > 0;i--){
    if(i < n) {
      dp[i] = make_pair(inf, i);
      while(v[first_point] - v[i] >= 1LL * t * a){
        first_point--;
      }
      while(v[second_point] - v[i] >= 1LL * t * a + 1LL * b * r){
        second_point--;
      }
      tmp = aint1.query(i + 1, first_point + 1);
      tmp.first -= 1LL * v[i] * b;
      dp[i] = min(dp[i], tmp);
      if(first_point < n){
        tmp = aint2.query(first_point + 1, second_point + 1);
        tmp.first += 1LL * t * a * b;
        tmp.first -= 1LL * t * a * a;
        tmp.first -= 1LL * v[i] * a;
        dp[i] = min(dp[i], tmp);
      }
      if(second_point < n){
        tmp = aint1.query(second_point + 1, n + 1);
        tmp.first += 1LL * r * a * b;
        tmp.first -= 1LL * b * v[i];
        tmp.first -= 1LL * r * b * b;
        dp[i] = min(dp[i], tmp);
      }
    }
    aint1.update(i, dp[i].first + 1LL * v[i] * b);
    aint2.update(i, dp[i].first + 1LL * v[i] * a);
  }

  int bestPosition = -1;

  for(int i = 1;i <= n;i++){
    if(bestPosition == -1 || 1LL * v[i] * a * b + dp[i].first < 1LL * v[bestPosition] * a * b + dp[bestPosition].first){
      bestPosition = i;
    }
    //cerr << i << " " << dp[i].first << " " << dp[i].second << "\n";
  }

  vector<int> positions = {bestPosition};

  for(int i = 0;i < (int)positions.size();i++){
    if(dp[positions[i]].second != -1){
      positions.push_back(dp[positions[i]].second);
    }
  }

  positions.pop_back();

  printf("%d\n", (int)positions.size());

  for(auto &it:positions) {
    printf("%d ", it - 1);
  }

  return 0;
}
