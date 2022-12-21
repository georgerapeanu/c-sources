#include <bits/stdc++.h>

using namespace std;

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

class PrefixFenwickTree{
  int n;
  vector<int> aib;

public:

  PrefixFenwickTree(int n) {
    this->n = n;
    this->aib = vector<int>(n + 1);
  }

  void update(int pos, int value) {
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] = aib[pos] + value;
    }
  }
  
  int query(int pos){
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
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

  FenwickTree aib_a(n + 1);
  FenwickTree aib_b(n + 1);
  PrefixFenwickTree aib_positions(n + 1);  
  map<int, vector<int> > pos_final_a;
  map<int, vector<int> > pos_final_b;
  map<int, vector<int> > pos_a;
  map<int, vector<int> > pos_b;

  for(int i = 1;i <= n;i++){
    aib_a.update(a[i], 1); 
    aib_b.update(b[i], 1); 
    aib_positions.update(i, 1);
    pos_final_a[a[i]].push_back(aib_a.query(a[i]));
    pos_final_b[b[i]].push_back(aib_b.query(b[i]));
    pos_a[a[i]].push_back(i);
    pos_b[b[i]].push_back(i);
  }


  vector<pair<int, int> > answer;
  for(auto it:pos_final_a){
    for(int j = 0;j < it.second.size();j++){
      if(pos_final_a[it.first][j] < pos_final_b[it.first][j]){
          
      } else {
      }
    }
  }

  //cout << ans << "\n";

  return 0;
}
