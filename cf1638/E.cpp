#include <bits/stdc++.h>

using namespace std;


class FenwickTree{
  int n;
  vector<long long> aib;

  public:
  FenwickTree(int n){
    this->n = n;
    this->aib = vector<long long>(n + 1, 0);
  }

  void update(int pos,int value){
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] += value;
    }
  }

  long long query(int pos){
    long long ans = 0;

    for(;pos;pos -= (-pos) & pos){
      ans += aib[pos];
    }
    return ans;
  }
};

struct node_t{
  int left,right,color;
  bool operator < (const node_t &other)const{
    if(left != other.left){
      return left < other.left;
    }
    if(right != other.right){
      return right < other.right;
    }
    return color < other.color;
  }
};

int n, q;
long long add[1000006];
set<node_t> intervals;

int get_color(int pos){
  set<node_t> :: iterator it = intervals.lower_bound({pos, pos, 0});
  if(it == intervals.end() || it->left > pos){
    it--;
  }
  return it->color;
}

int main(){

  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  cin.tie(0);cout.tie(0);

  cin >> n >> q;

  FenwickTree aib(n);
  intervals.insert({1, n, 1});

  while(q--){
    string op;
    cin >> op;
    if(op == "Color"){
      int l, r, c;
      cin >> l >> r >> c;

      vector<node_t> tmp;

      set<node_t> :: iterator ant;
      set<node_t> :: iterator it = intervals.lower_bound({r + 1, r + 1, 0});
      if(it != intervals.begin()){
        it--;
      }
      if(it != intervals.end() && it->left <= r){
        while(it->right >= l){
          tmp.push_back(*it);
          if(it == intervals.begin()){
            intervals.erase(it);
            break;
          }
          ant = prev(it);
          intervals.erase(it);
          it = ant;
        }
      }

      for(auto &it:tmp){
        if(it.left < l){
          intervals.insert({it.left, l - 1, it.color});
        }
        if(it.right > r){
          intervals.insert({r + 1, it.right, it.color});
        }
        it.left = max(it.left, l);
        it.right = min(it.right, r);
      }

      for(auto it:tmp){
        aib.update(it.left, add[it.color] - add[c]);
        aib.update(it.right + 1, -add[it.color] + add[c]);
      }
      intervals.insert({l,r,c});

    }else if(op == "Add"){
      int c, x;
      cin >> c >> x;
      add[c] += x;
    }else{
      int x;
      cin >> x;
      cout << aib.query(x) + add[get_color(x)] << "\n";
    }
  }

  return 0;
}
