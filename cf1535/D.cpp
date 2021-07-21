#include <bits/stdc++.h>

using namespace std;

class SegmentTree{
  struct node_t{
    int min_value;
    int fr;
    int lazy;

    node_t(){
      min_value = 1e9;
      fr = 0;
      lazy = 0;
    }

    node_t operator + (const node_t &other)const{
      node_t ans;
      ans.min_value = min(this->min_value,other.min_value);
      ans.fr = 0;
      if(this->min_value <= other.min_value){
        ans.fr += this->fr;
      }
      if(this->min_value >= other.min_value){
        ans.fr += other.fr;
      }
      ans.lazy = 0;
      return ans;
    }

    void propagate(int lazy){
      this->min_value += lazy;
      this->lazy += lazy;
    }
  };

  int n;
  vector<node_t> aint;

  void propagate(int nod,int st,int dr){
    if(aint[nod].lazy == 0 || st == dr){
      return ;
    }
    aint[nod * 2].propagate(aint[nod].lazy);
    aint[nod * 2 + 1].propagate(aint[nod].lazy);

    aint[nod].lazy = 0;
  }

  void build(int nod,int st,int dr){
    if(st == dr){
      aint[nod] = node_t();
      aint[nod].min_value = 0;
      aint[nod].fr = 1;
      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void update(int nod,int st,int dr,int l,int r,int value){
    propagate(nod,st,dr);
    if(dr < l || st > r){
      return ;
    }
    if(l <= st && dr <= r){
      aint[nod].propagate(value);
      return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,value);
    update(nod * 2 + 1,mid + 1,dr,l,r,value);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];

    return ;
  }

public:

  SegmentTree(int n){
    this->n = n;
    this->aint = vector<node_t>(4 * n + 5,node_t());
    build(1,1,n);
  }

  void update(int l,int r,int value){
    update(1,1,n,l,r,value);
  }

  int query(){
    propagate(1,1,n);
    return aint[1].fr * (aint[1].min_value == 0);
  }

};

int k;
int n;
string s;
int q;

SegmentTree aint(1);

pair<int,int> get_range(int pos){
  int tmp = k - 1;
  int length = 1;
  while((pos >> tmp) & 1){
    pos ^= (1 << tmp);
    tmp--;
    length <<= 1;
  }
  
  return make_pair(pos * 2 * length + 1,length);///START,LENGTH
}

void process(const string &s){
  for(int i = 0;i < (int)s.size();i++){
    pair<int,int> tmp = get_range(i);
    if(s[i] == '0'){
      aint.update(tmp.first + tmp.second,tmp.first + 2 * tmp.second - 1,1);
    }else if(s[i] == '1'){
      aint.update(tmp.first,tmp.first + tmp.second - 1,1);
    }
  }
}

void add(string &s,int p,int c){
  p--;
  s[p] = c;
  
  pair<int,int> tmp = get_range(p);
  if(s[p] == '0'){
    aint.update(tmp.first + tmp.second,tmp.first + 2 * tmp.second - 1,1);
  }else if(s[p] == '1'){
    aint.update(tmp.first,tmp.first + tmp.second - 1,1);
  }
}

void remove(const string &s,int p){
  p--;
  pair<int,int> tmp = get_range(p);
  if(s[p] == '0'){
    aint.update(tmp.first + tmp.second,tmp.first + 2 * tmp.second - 1,-1);
  }else if(s[p] == '1'){
    aint.update(tmp.first,tmp.first + tmp.second - 1,-1);
  }
}

int main(){

  cin >> k;
  n = (1 << k) - 1;

  cin >> s;

  aint = SegmentTree(n + 1);

  process(s);

  cin >> q;

  for(int i = 1;i <= q;i++){
    int p;
    char c;
    cin >> p >> c;
    remove(s,p);
    add(s,p,c);
    cout << aint.query() << "\n";
  }

  return 0;
}
