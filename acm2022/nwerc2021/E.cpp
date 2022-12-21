#include <bits/stdc++.h>

using namespace std;

const size_t LIM = 2e5;

class FenwickTree{
  int n;
  vector<int> aib;

public:

  FenwickTree(int n) {
    this->n = n;
    this->aib = vector<int>(n + 1);
  }

  void update(int pos, int value) {
    for(;pos;pos -= (-pos) & pos){
      aib[pos] = aib[pos] + value;
    }
  }
  
  int query(int pos){
    int ans = 0;
    for(;pos <= n;pos += (-pos) & pos){
      ans = ans + aib[pos];
    }
    return ans;
  }
};

int main(){

  int n;
  cin >> n;
  vector<int> a(n + 1), b(n + 1);

  for(int i = 1;i <= n;i++){
    cin >> a[i];
  }
  
  for(int i = 1;i <= n;i++){
    cin >> b[i];
  }

  map<int, int> to_norm;
  for(auto &it:a){
    to_norm[it] = 0;
  }

  int last_id = 0;
  for(auto &it:to_norm){
    it.second = ++last_id;
  }

  for(auto &it:a){
    it = to_norm[it];
  }
  
  for(auto &it:b){
    it = to_norm[it];
  }
  
  vector<vector<int> > pos_a(last_id + 1);
  vector<vector<int> > pos_b(last_id + 1);

  FenwickTree aib_a(last_id);
  FenwickTree aib_b(last_id);
  vector<vector<int> > pos_final_a(last_id + 1);
  vector<vector<int> > pos_final_b(last_id + 1);
  for(int i = 1;i <= n;i++){
    pos_a[a[i]].push_back(i);
    pos_b[b[i]].push_back(i);
    aib_a.update(a[i], 1);
    aib_b.update(b[i], 1);
    pos_final_a[a[i]].push_back(aib_a.query(a[i]));
    pos_final_b[b[i]].push_back(aib_b.query(b[i]));
  }

  vector<int> __next(n + 2, 0);
  vector<int> __prev(n + 2, 0);
  vector<int> __value(n + 2, 0);
  for(int i = 1;i <= n;i++){
    __next[i] = i + 1;
    __prev[i] = i - 1;
    __value[i] = i;
  }

  vector<pair<int, int> > answer;
  long long ans = 0;
  for(int i = 0;i < (int)pos_final_a.size();i++){
    for(int j = 0;j < (int)pos_final_a[i].size();j++){
      ans += abs(pos_final_a[i][j] - pos_final_b[i][j]);
    }
  }
  for(int i = 0;i < (int)pos_a.size() && answer.size() < LIM;i++){

    vector<pair<int, int> > order;
    vector<pair<int, int> > current;
    for(int j = 0;j < (int)pos_a[i].size() && answer.size() < LIM;j++){
      int source_index = pos_a[i][j];
      int target = pos_b[i][j];
      if(__value[source_index] > target){
        while(!current.empty()){
          order.push_back(current.back());
          current.pop_back();
        }
        current.push_back({source_index, target});
      } else {
        current.push_back({source_index, target});
      }
    }
    while(!current.empty()){
      order.push_back(current.back());
      current.pop_back();
    }
    for(auto it:order){
      int source_index = it.first;
      int target = it.second;
      vector<pair<int, int> > toUpdate;
      __next[__prev[source_index]] = __next[source_index];
      __prev[__next[source_index]] = __prev[source_index];
      while(__value[source_index] < target && answer.size() < LIM){
        answer.push_back({__value[source_index], __value[__next[source_index]]});
        toUpdate.push_back({__next[source_index], __value[source_index]});
        source_index = __next[source_index];
      }
      while(__value[source_index] > target && answer.size() < LIM){
        answer.push_back({__value[source_index], __value[__prev[source_index]]});
        toUpdate.push_back({__prev[source_index], __value[source_index]});
        source_index = __prev[source_index];
      }
      for(auto it:toUpdate){
        __value[it.first] = it.second;
      }
    }
  }

  cout << ans << "\n";
  for(auto it:answer){
    cout << it.first << " " << it.second << "\n";
  }
  
  return 0;
}
