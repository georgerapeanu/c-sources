#include <set>
#include "weirdtree.h"
#include <vector>
#include <algorithm>

using namespace std;

struct node_t{
  int l,r;
  int value;

  node_t(int pos,int value){
    this->l = this->r = pos;
    this->value = value;
  }

  node_t(int l,int r,int value){
    this->l = l;
    this->r = r;
    this->value = value;
  }

  bool operator < (const node_t &other)const{
    if(l != other.l){
      return l < other.l;
    }
    if(r != other.r){
      return r < other.r;
    }
    return value < other.value;
  }

  void merge(const node_t &other){
    this->l = min(this->l, other.l);
    this->r = max(this->r, other.r);
    this->value = min(this->value, other.value);///check this
  }

  vector<node_t> cut(int pos){
    if(pos < this->l || pos >= this->r){
      return {*this};
    }
    node_t fst = node_t(this->l,pos,this->value);
    node_t snd = node_t(pos + 1,this->r,this->value);
    return {fst,snd};
  }

  int length()const{
    return r - l + 1;
  }
  
  long long sum(int l,int r)const{
    return 1LL * this->value * max(0, min(r,this->r) - max(l,this->l) + 1);
  }
};

set<node_t> values;

bool are_mergeable(const node_t &fst, const node_t &snd){
  if(fst.value != snd.value){
    return false;
  }
  if(fst.l != snd.r + 1 && fst.r + 1 != snd.l){
    return false;
  }
  return true;
}

void insert_node(node_t it){
    set<node_t> :: iterator it2 = values.lower_bound(it);
    if(it2 != values.end() && are_mergeable(it,*it2)){
      node_t tmp = *it2;
      values.erase(it2);
      it.merge(tmp);
    }
    it2 = values.lower_bound(it);
    if(it2 != values.begin()){
      it2--;
      if(are_mergeable(it,*it2)){
        node_t tmp = *it2;
        values.erase(it2);
        it.merge(tmp);
      }
    }
    values.insert(it);
}

void initialise(int n, int q, int h[]){
  node_t active(1,h[1]);

  for(int i = 2;i <= n;i++){
    if(h[i - 1] == h[i]){
      active.merge(node_t(i,h[i]));
    }else{
      values.insert(active);
      active = node_t(i,h[i]);
    }
  }

  values.insert(active);

}

void cut(int l, int r, int k){
  vector<node_t> nodes;

  set<node_t> :: iterator it = values.lower_bound(node_t(l, 0));
  if(it->l > l){
    it--;
  }
  
  while(it != values.end() && it->l <= r){
    nodes.push_back(*it);
    it++;
  }

  for(auto it:nodes){
    values.erase(it);
  }

  if(nodes[0].l < l){
    vector<node_t> tmp = nodes[0].cut(l - 1);
    insert_node(tmp[0]);
    nodes[0] = tmp[1];
  }
  if(nodes.back().r > r){
    vector<node_t> tmp = nodes.back().cut(r);
    insert_node(tmp[1]);
    nodes.back() = tmp[0];
  }

  sort(nodes.begin(),nodes.end(),[&](const node_t &a, const node_t &b){
    if(a.value != b.value){
      return a.value > b.value;
    }
    if(a.l != b.l){
      return a.l < b.l;
    }
    return a.r < b.r;
  });
  int active_len = 0;
  int active_value = 0;
  int break_index = (int)nodes.size();
  for(int i = 0;i < (int)nodes.size();i++){
    if(active_len == 0 || active_value - nodes[i].value <= k / active_len){
      k -= (active_value - nodes[i].value) * active_len;
      active_len += nodes[i].length();
      active_value = nodes[i].value;
    }else{
      break_index = i;
      break;
    }
  }

  vector<node_t> active;
  int total_length = 0;

  for(int i = 0;i < (int)nodes.size();i++){
    if(i >= break_index){
      insert_node(nodes[i]);
    }else{
      nodes[i].value = nodes[break_index - 1].value;
      active.push_back(nodes[i]); 
      total_length += nodes[i].length();
    }
  }
  
  sort(active.begin(),active.end());
  int delta = k / total_length;
  k = k - delta * total_length;
  for(auto it:active){
    it.value -= delta;
    if(it.length() <= k){
      k -= it.length();
      it.value--;
    }else if(k > 0){
      vector<node_t> tmp = it.cut(it.l + k - 1);
      tmp[0].value -= 1;
      tmp[0].value = max(tmp[0].value, 0);
      insert_node(tmp[0]);
      it = tmp[1];
      k = 0;
    }
    it.value = max(it.value,0);
    insert_node(it);
  }
}

void magic(int i, int x){
  set<node_t> :: iterator it = values.lower_bound(node_t(i, 0));
  if(it->l > i){
    it--;
  }
  node_t tmp = *it;
  values.erase(it);
  vector<node_t> nodes = tmp.cut(i);
  vector<node_t> new_nodes;

  for(auto node:nodes){
    vector<node_t> split_nodes = node.cut(i - 1);
    for(auto it:split_nodes){
      new_nodes.push_back(it);
    }
  }
  
  for(auto it:new_nodes){
    if(it.l <= i && i <= it.r){
      it.value = x;
    }
    insert_node(it);
  }
}

long long inspect(int l, int r){
  long long ans = 0;

  set<node_t>::iterator it = values.lower_bound(node_t(l,0));
  if(it != values.begin()){
    it--;
  }

  while(it != values.end() && it->l <= r){
    ans += it->sum(l,r);
    it++;
  }
  return ans;
}
