#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

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

struct data_t{
  int ways;
  int length;

  data_t(){
    ways = length = 0;
  }

  data_t operator + (const data_t &other) const {
    data_t answer;
    answer.length = max(this->length, other.length);
    if(this->length == answer.length){
      answer.ways = add(answer.ways, this->ways);
    }
    if(other.length == answer.length){
      answer.ways = add(answer.ways, other.ways);
    }
    return answer;
  }
};

class FenwickTree{
  int n;
  vector<data_t> aib;

public:

  FenwickTree(int n) {
    this->n = n;
    this->aib = vector<data_t>(n + 1);
  }

  void update(int pos, data_t value) {
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] = aib[pos] + value;
    }
  }
  
  data_t query(int pos){
    data_t ans = data_t();
    for(;pos;pos -= (-pos) & pos){
      ans = ans + aib[pos];
    }
    return ans;
  }
};

int main(){

  int n;
  
  cin >> n;

  vector<int> v(n + 1, 0);

  map<int, int> to_norm;
  for(int i = 1;i <= n;i++){
    cin >> v[i];
    to_norm[v[i]] = 0;
  }

  int last_id = 1;

  for(auto &it:to_norm){
    it.second = last_id++;
  }

  for(int i = 1;i <= n;i++){
    v[i] = to_norm[v[i]];
  }

  FenwickTree aib(n);

  vector<data_t> best_answers(n + 1);

  for(int i = 1;i <= n;i++){
    data_t tmp = aib.query(v[i] - 1);
    tmp.length += 1;

    if(tmp.length == 1){
      tmp.ways = add(tmp.ways, 1);
    }
    if(tmp.length > best_answers[v[i]].length){
      best_answers[v[i]] = tmp;
      aib.update(v[i], tmp);
    } else if(tmp.length == best_answers[v[i]].length){
      tmp.ways = sub(tmp.ways, best_answers[v[i]].ways);
      best_answers[v[i]] = best_answers[v[i]] + tmp;
      aib.update(v[i], tmp);
    }

  }

  printf("%d\n", aib.query(last_id - 1).ways);

  return 0;
}
