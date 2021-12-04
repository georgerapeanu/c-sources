#include <bits/stdc++.h>

using namespace std;

const int TMAX = 50;
const int inf = 1e9;

///Copied node_t(modified)
///Copied segment tree from here to but is now heavily modified
///Link: https://infoarena.ro/job_detail/2789950?action=view-source

struct node_t{
  int t;
  int value;
  int len;
  vector<pair<int,int>> __left,__right;
  int lazy;

  /// should be a neutral node for both lazy and query operations
  node_t(){
    t = 0;
    value = inf;
    len = 0;
    __left = __right = vector<pair<int,int>>();
    lazy = 0;
  }

  /// aditional constructors for specific problem
  node_t(int t){
    this->t = t;
    this->value = inf;
    this->__left = vector<pair<int,int>>();
    this->__right = vector<pair<int,int>>();
    this->lazy = 0;
  }

  node_t(int t,int value){
    this->t = t;
    this->value = (t == 1 && value == 1 ? 1:inf);
    this->__left = vector<pair<int,int>>();
    this->__right = vector<pair<int,int>>();
    
    this->__left.push_back({1,value});
    this->__right.push_back({1,value});

    this->len = 1;
    this->lazy = 0;
  }

  /// associative internal operation
  node_t operator + (const node_t &other)const{
    if(this->t == 0){
      return other;
    }
    if(other.t == 0){
      return *this;
    }
    node_t ans(this->t);
    ans.len = this->len + other.len;
    
    vector<int> marked(ans.t + 1,0);

    for(auto it:this->__left){
      ans.__left.push_back(it);
      marked[it.second] = true;
    }
    for(auto it:other.__left){
      if(marked[it.second] == false){
        ans.__left.push_back({it.first + this->len,it.second});
        marked[it.second] = true;
      }
    }
    
    marked = vector<int>(ans.t + 1,0);

    for(auto it:other.__right){
      ans.__right.push_back(it);
      marked[it.second] = true;
    }
    for(auto it:this->__right){
      if(marked[it.second] == false){
        ans.__right.push_back({it.first + other.len,it.second});
        marked[it.second] = true;
      }
    }
    ans.value = min(this->value,other.value);

    int cnt = 0;
    vector<int> fr(ans.t + 1,0);
    vector<pair<int,int> > tmp;

    for(int i = (int)this->__right.size() - 1;i >= 0 ;i--){
      tmp.push_back({-this->__right[i].first + 1,this->__right[i].second});
    }
    for(auto it:other.__left){
      tmp.push_back(it);
    }
    
    bool found = false;
    int l = 0;

    for(int r = 0;r < (int)tmp.size();r++){
      fr[tmp[r].second]++;
      if(fr[tmp[r].second] == 1){
        cnt++;
      }
      if(cnt == ans.t){
        found = true;
      }
      while(l <= r && cnt == ans.t){
        fr[tmp[l].second]--;
        if(fr[tmp[l].second] == 0){
          cnt--;
        }
        l++;
      }
      if(found){
        ans.value = min(ans.value,tmp[r].first - tmp[l - 1].first + 1);
      }
    }

    return ans;
  }

  /// internal propagation law
  node_t propagate(int lazy,int st,int dr){
    /// no need
  }

  void display()const{
    printf("=========debug=======\n");
    printf("value: %d\n",value);
    for(auto it:__left)printf("(%d,%d) ",it.first,it.second);printf("\n");
    for(auto it:__right)printf("(%d,%d) ",it.first,it.second);printf("\n");

    printf("=====================\n");
  }
};

template <class T>
class SegmentTree{
  
  int n;
  vector<T> aint;

  public:

  SegmentTree(const vector<T> &v){
    this->n = v.size();
    this->aint = vector<T>(2 * n + 5,T());

    for(int i = 0;i < n;i++){
      aint[i + n] = v[i];
    }
    for(int i = n - 1;i >= 1;i--){
      aint[i] = aint[2 * i] + aint[2 * i + 1];      
    }
  }

  ///update with a node
  void updateSet(int pos,T val){
    for (aint[pos += n] = val; pos >>= 1; ) {
      aint[pos] = aint[2 * pos] + aint[2 * pos + 1];
    }
  }


  T query(int l,int r){
    T lft = T();
    T rgt = T();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lft = lft + aint[l++];
      if (r & 1) rgt = aint[--r] + rgt;
    }
    return lft + rgt;
  }
};
///end copy Segment tree

const int LEN = 1 << 12;
char buff[LEN];

int ind = LEN - 1;

int i32(){
  int ans = 0;
  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }
  
  while('0' <= buff[ind] && buff[ind] <= '9'){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }
  return ans;
}

int main(){

  int n,t,m;

  n = i32();
  t = i32();
  m = i32();

  vector<node_t> v(n,node_t());

  for(auto &it:v){
    int value;
    value = i32();
    it = node_t(t,value);
  }
  
  SegmentTree<node_t> aint(v);

  while(m--){
    int op;
    op = i32();
    if(op == 1){
      int a,b;
      a = i32();
      b = i32();
      aint.updateSet(a - 1,node_t(t,b));
    }else{
      int ans = aint.query(0,n - 1).value;
      if(ans == inf){
        ans = -1;
      }
      printf("%d\n",ans);
    }
  }

//  (node_t(3,3) + node_t(3,1) + node_t(3,2) + node_t(3,1)).display();

  return 0;
}
