#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;

struct node_t{
  long long __min;
  long long __max;
  long long __sum;
  pair<long long, long long> lazy;

  node_t(){
    this->__min = inf;
    this->__max = -inf;
    this->__sum = 0;
    this->lazy = {1, 0};
  }

  node_t(const pair<int, int> &value) {
    this->__min = value.first;
    this->__max = value.first;
    this->__sum = value.second;
    this->lazy = {1, 0};
  }

  node_t operator + (const node_t& other)const{
    node_t answer;
    answer.__min = min(this->__min, other.__min);
    answer.__max = max(this->__max, other.__max);
    answer.__sum = this->__sum + other.__sum;
    answer.lazy = {1, 0};
    return answer;
  }

  void propagate(const pair<long long, long long> &lazy) {
    this->__min = lazy.first * __min + lazy.second;
    this->__max = lazy.first * __max + lazy.second;
    if(this->__min > this->__max){
      swap(this->__min, this->__max);
    }
    this->lazy = {lazy.first * this->lazy.first, lazy.first * this->lazy.second + lazy.second};
  }
};

class SegmentTree{
  int n;
  vector<node_t> aint;

  void build(int nod, int st, int dr, const vector<pair<int, int> > &values) {
    if(st == dr){
      aint[nod] = node_t(values[st]);
      return ;
    }

    int mid = (st + dr) / 2;
    build(nod * 2, st, mid, values);
    build(nod * 2 + 1, mid + 1, dr, values);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propagate(int nod, int st, int dr){
    if(st == dr){
      return ;
    }
    aint[nod * 2].propagate(aint[nod].lazy);
    aint[nod * 2 + 1].propagate(aint[nod].lazy);
    aint[nod].lazy = {1, 0};
  }
  
  void update(int nod, int st, int dr, int l, int r, const pair<long long, long long> &lazy) {
    propagate(nod, st , dr);
    if(r < st || l > dr){
      return ;
    }
    if(l <= st && dr <= r){
      aint[nod].propagate(lazy);
      return ;
    }

    int mid = (st + dr) / 2;
    update(nod * 2, st, mid, l, r, lazy);
    update(nod * 2 + 1, mid + 1, dr, l, r, lazy);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void getBuckets(int nod, int st, int dr, int l, int r, vector<node_t> &answer) {
    propagate(nod, st, dr);
    if(dr < l || st > r){
      return ;
    }
    if(l <= st && dr <= r && aint[nod].__min == aint[nod].__max){
      answer.push_back(aint[nod]); 
      return ;
    }

    int mid = (st + dr) / 2;
    getBuckets(nod * 2, st, mid, l, r, answer);
    getBuckets(nod * 2 + 1, mid + 1, dr, l, r, answer);
  }

public:
  
  SegmentTree(const vector<pair<int, int> > &v){
    this->n = v.size();
    this->aint = vector<node_t>(4 * n + 5);
    this->build(1, 1, n, v);
  }

  void updateSet(int st, int dr, long long value){
    this->update(1, 1, n, st, dr, make_pair(0, value)); 
  }
  
  void updateAdd(int st, int dr, long long value){
    this->update(1, 1, n, st, dr, make_pair(1, value)); 
  }

  vector<pair<long long, long long> > getBuckets(int l, int r){
    vector<node_t> node_answer;
    this->getBuckets(1, 1, n, l, r, node_answer);
    sort(node_answer.begin(), node_answer.end(), [](const node_t &a, const node_t &b){
      return a.__min < b.__min;  
    });
    vector<pair<long long, long long > > answer;
    for(auto it:node_answer){
      if(answer.empty() || answer.back().first != it.__min){
        answer.push_back({it.__min, 0});
      }
      answer.back().second += it.__sum;
    }
    return answer;
  }
  
};

int main(){

  int n, q;
  scanf("%d %d", &n, &q);
  vector<pair<int, int> > values(n + 1);

  for(int i = 1;i <= n;i++){
    scanf("%d", &values[i].first);
  }
  
  for(int i = 1;i <= n;i++){
    scanf("%d", &values[i].second);
  }

  SegmentTree aint(values);

  while(q--){
    int t;
    scanf("%d", &t);
    if(t == 1){
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      aint.updateAdd(l, r, x);
    } else {
      int l, r;
      scanf("%d %d", &l, &r);
      vector<pair<long long, long long> > buckets = aint.getBuckets(l, r);
      long long total_sum = 0;
      for(auto it:buckets){
  //      printf("debug bucket %lld %lld\n", it.first, it.second);
        total_sum += it.second;  
      }

      long long prefix_sum = 0;
      long long level = 0;

      for(auto it:buckets){
        if(prefix_sum - (total_sum - prefix_sum) >= 0){
          break;
        }
        prefix_sum += it.second;
        level = it.first;
      }
      aint.updateSet(l, r, level);
      printf("%lld\n", level);
    }
  }

  return 0;
}
