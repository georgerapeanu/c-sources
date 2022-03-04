#include "weirdtree.h"
#include <vector>
#include <algorithm>

using namespace std;

struct node_t{
  int max;
  int pos;
  long long sum;

  node_t(){
    ;
  }

  node_t(int max,int pos,long long sum){
    this->max = max;
    this->pos = pos;
    this->sum = sum;
  }

  node_t operator + (const node_t &other)const{
    node_t ans;
    ans.sum = this->sum + other.sum;
    if(this->max < other.max){
      ans.max = other.max;
      ans.pos = other.pos;
    }else if(this->max == other.max){
      if(this->pos < other.pos){
        ans.max = this->max;
        ans.pos = this->pos;
      }else{
        ans.max = other.max;
        ans.pos = other.pos;
      }
    }else{
      ans.max = this->max;
      ans.pos = this->pos;
    }
    return ans;
  }
};

class FastSegmentTree{
  int n;
  vector<node_t> aint;

  void build(const vector<int> &v){
    for(int i = 0;i < n;i++){
      aint[i + n] = node_t(v[i],i,v[i]);
    }
    for(int i = 2 * n - 1;i > 1;i--){
      aint[i >> 1] = aint[i] + aint[i ^ 1];
    }
  }

  public:

  FastSegmentTree(){
    ;
  }

  FastSegmentTree(const vector<int> &v){
    this->n = (int)v.size();
    this->aint = vector<node_t>(2 * n, node_t());
    build(v);
  }

  void update(int pos,int value){
    for(aint[pos += n] = node_t(value, pos, value);pos > 1;pos >>= 1){
      aint[pos >> 1] = aint[pos] + aint[pos ^ 1];
    }
  }

  node_t query(int l,int r){
    node_t ans(-100,0,0);
    for(l += n, r += n;l < r;l >>= 1,r >>= 1){
      if(l & 1)ans = ans + aint[l++];
      if(r & 1)ans = ans + aint[--r];
    }
    return ans;
  }

  void multiple_updates(const vector<pair<int,int> > &updates){
    vector<int> positions;
    vector<int> next_positions; 
    for(auto it:updates){
      aint[it.first + n] = node_t(it.second,it.first,it.second);
      positions.push_back(it.first + n);
    }

    while(!positions.empty()){
      next_positions.clear();
      for(auto it:positions){
        if(next_positions.empty() || next_positions.back() != (it >> 1)){
          if((it >> 1) > 1){
            next_positions.push_back(it >> 1);
          }
          aint[it >> 1] = aint[it] + aint[it ^ 1];
        }
      }
      positions.swap(next_positions);
    }
  }
}aint;

void initialise(int n, int q, int h[]){
  vector<int> vh(n,0);
  for(int i = 1;i <= n;i++){
    vh[i - 1] = h[i];
  }
  aint = FastSegmentTree(vh);
}

void cut(int l, int r, int k){
  node_t tmp = aint.query(l - 1,r);
  vector<int> positions;
  int last_value = 1e9;
  int length = 0;

  while(length != r - l + 1 && k != 0){
    node_t nxt = aint.query(l - 1, r);
    if(1LL * (last_value - nxt.max) * length <= k){
      positions.push_back(nxt.pos);
      k -= (last_value - nxt.max) * length;
      length++;
      last_value = nxt.max;
      aint.update(nxt.pos, -1);
    }else{
      break;
    }
  }
  sort(positions.begin(),positions.end());
  last_value -= k / length;
  k %= length;
  vector<pair<int,int> > updates;
  for(int i = 0;i < (int)positions.size();i++){
    updates.push_back(make_pair(positions[i], max(0, last_value - (i < k))));
  }
  k = 0;
  aint.multiple_updates(updates);
}

void magic(int i, int x){
  aint.update(i - 1, x);
}

long long inspect(int l, int r){
  return aint.query(l - 1,r).sum;
}
