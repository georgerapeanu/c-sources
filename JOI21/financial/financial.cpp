#include <bits/stdc++.h>

using namespace std;

class DSU{
  int n;
  vector<int> father;
  vector<int> weight;
  vector<int> left;

public:

  DSU(int n){
    this->n = n;
    this->father = vector<int>(n, -1);
    this->weight = vector<int>(n, 1);
    this->left = vector<int>(n, 0);
    for(int i = 0;i < n;i++){
      this->left[i] = i;
    }
  }

  int find_root(int nod){
    if(father[nod] == -1){
      return nod;
    }
    return father[nod] = find_root(father[nod]);
  }

  bool unite(int x, int y){
//    printf("unite %d %d\n", x, y);
    x = find_root(x);
    y = find_root(y);

    if(x == y){
      return false;
    }
    
    if(weight[x] < weight[y]){
      swap(x, y);
    }
    father[y] = x;
    weight[x] += weight[y];
    left[x] = min(left[x], left[y]);

    return true;
  }

  int get_left(int nod){
    return left[find_root(nod)];
  }
};

class SegmentTree{ /// 0 indexed
  int n;
  vector<int> aint;
  
  public:
  SegmentTree(int n){
    this->n = n;
    this->aint = vector<int>(2 * n + 5);
  }

  void update(int pos,int value){
    for(aint[pos += n] = value;pos > 1;pos >>= 1){
      aint[pos >> 1] = max(aint[pos ^ 1], aint[pos]);
    }
  }

  int query(int l, int r){
    int ans = 0;
    for(l += n, r += n;l < r; l >>= 1, r>>= 1){
      if(l & 1){
        ans = max(ans, aint[l++]);
      }
      if(r & 1){
        ans = max(ans, aint[--r]);
      }
    }
    return ans;
  }
};

int main(){
  int n, d;

  scanf("%d %d", &n, &d);
  vector<int> v(n, 0);

  for(auto &it:v){
    scanf("%d", &it);
  }

  vector<pair<int,int> > pos;
  
  for(int i = 0;i < n;i++){
    pos.push_back({v[i],i});
  }
  sort(pos.begin(), pos.end(), [&](const pair<int,int> &a, const pair<int,int> &b){return make_pair(a.first,-a.second) < make_pair(b.first,-b.second);});

  SegmentTree aint(n);
  DSU dsu(n);
  set<int> active;
  active.insert(-1);
  active.insert(n);
  int ans = 0;

  for(auto it:pos){
    set<int> :: iterator n_it = active.lower_bound(it.second); 
    if(*n_it < n && *n_it - it.second <= d){
      dsu.unite(*n_it, it.second); 
    }
    n_it--;
    if(*n_it != -1 && it.second - *n_it <= d){
      dsu.unite(*n_it, it.second); 
    }
    
//    printf("debug %d %d is left %d\n", it.first, it.second, dsu.get_left(it.second));
    int local_ans = 1 + aint.query(dsu.get_left(it.second), it.second);
    ans = max(ans, local_ans);
    aint.update(it.second, local_ans);
//    printf("activated %d with %d\n", it.second, local_ans);
    active.insert(it.second);
  }

  printf("%d\n", ans);

  return 0;
}
