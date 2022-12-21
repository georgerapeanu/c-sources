#include <bits/stdc++.h>

using namespace std;

struct team_t{
  int duration;
  int profit;
};

struct dp_state_t{
  int segment;
  int space_taken;

  dp_state_t(){
    segment = 0;
    space_taken = 0;
  }

  bool operator < (const dp_state_t &other)const{
    if(this->segment != other.segment){
      return this->segment < other.segment;
    }
    return this->space_taken < other.space_taken;
  }
};

int main(){

  int h, t;
  scanf("%d %d", &h, &t);
  vector<int> heights(h + 1, 0);
  
  long long area = 0;
  for(int i = 1;i <= h;i++){
    scanf("%d", &heights[i]);
    area += heights[i];
    heights[i] = min(heights[i], t);
  }
  
  vector<team_t> teams(t);
  for(auto &it:teams){
    cin >> it.duration;
    cin >> it.profit;
  }

  vector<int> lengths;
  for(int i = 1;i <= t;i++){
    int current_length = 0;
    for(int j = 1;j <= h;j++){
      if(heights[j] < i){
        if(current_length > 0){
          lengths.push_back(current_length);
        }
        current_length = 0;
      } else {
        current_length++;
      }
    }
    if(current_length > 0){
      lengths.push_back(current_length);
    }
  }
 
  sort(lengths.begin(), lengths.end());
  vector<dp_state_t> dp(1 << t);
  for(int conf = 1;conf < (1 << t);conf++){
    dp[conf].segment = (int)lengths.size() + 1;
    dp[conf].space_taken = 0;
  }

  for(int conf = 0;conf < (1 << t);conf++){
    if(dp[conf].segment >= (int)lengths.size()){
      continue;
    }
    for(int i = 0;i < t;i++){
      if((conf >> i) & 1){
        continue; 
      }
      dp_state_t nxt = dp[conf];
      if(nxt.space_taken + teams[i].duration  <= lengths[nxt.segment]){
        nxt.space_taken += teams[i].duration;
      }else{
        int next_segment = lower_bound(lengths.begin() + nxt.segment + 1, lengths.end(), teams[i].duration) - lengths.begin();
        nxt.segment = next_segment;
        nxt.space_taken = teams[i].duration;
      }
      if(nxt < dp[conf | (1 << i)]){
        dp[conf | (1 << i)] = nxt;
      }
    }
  }

  int answer = 0;

  for(int conf = 0;conf < (1 << t);conf++){
    if(dp[conf].segment >= (int)lengths.size()){
      continue;
    }
    int local_answer = 0;
    long long total_length = 0;
    for(int i = 0;i < t;i++){
      if((conf >> i) & 1){
        local_answer += teams[i].profit;
        total_length += teams[i].duration;
      }
    }
    if(total_length == area){
      answer = max(answer, local_answer);
    }
  }

  printf("%d\n", answer);

  return 0;
}
