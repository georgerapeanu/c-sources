#include <bits/stdc++.h>

using namespace std;

struct dsu_data_t{
  long long sum;
  int left;
  int right;
};


class DSU{
  int n;
  vector<dsu_data_t> dsu_data;
  vector<int> father;
 
public:
  DSU(const vector<long long> &v){
    this->n = (int)v.size();
    this->father = vector<int>(n, -1);
    dsu_data = vector<dsu_data_t>(n);
    for(int i = 0;i < n;i++){
      dsu_data[i] = {v[i], i, i};
    }
  }

  int find_root(int node){
    if(father[node] == -1){
      return node;
    }
    return father[node] = find_root(father[node]);
  }

  bool unite(int x, int y){
    x = find_root(x);
    y = find_root(y);
    if(x == y){
      return false;
    }
    
    if((dsu_data[y].right + 1) % n == dsu_data[x].left){
      swap(x, y);
    }
    
    if((dsu_data[x].right + 1) % n != dsu_data[y].left){
      assert(false);
    }
    
    dsu_data[x].right = dsu_data[y].right;
    dsu_data[x].sum += dsu_data[y].sum;
    father[y] = x;
    return true;
  }

  dsu_data_t get_data(int node){
    return dsu_data[node];
  }
};

bool ok(const vector<long long> &v, long long start){
//  cerr << "trying " << start << "\n";
  DSU dsu(v);

  vector<int> q;

  for(int i = 0;i < (int)v.size();i++){
    if(v[i] <= start){
      q.push_back(i);
    }
  }

  int n = v.size();

  for(int i = 0;i < (int)q.size();i++){
    int pos = q[i];
    dsu_data_t data = dsu.get_data(dsu.find_root(pos));
    dsu_data_t prev_data = dsu.get_data(dsu.find_root((data.left + n - 1) % n));
    dsu_data_t next_data = dsu.get_data(dsu.find_root((data.right +  1) % n));
    //cerr << "visiting " << data.left << " " << data.right << " " << data.sum << "\n";
    bool done_something = false;

    if(prev_data.sum <= start + data.sum){
      done_something |= dsu.unite(prev_data.right, data.left);
    }
    if(next_data.sum <= start + data.sum){
      done_something |= dsu.unite(data.right, next_data.left);
    }
    if(done_something){
      q.push_back(dsu.find_root(pos));
    }
  }

  dsu_data_t data = dsu.get_data(dsu.find_root(0));
  if(data.left == 0 && data.right == n - 1){
    return true;
  }
  return data.left == data.right + 1;
}

int main(){

  int n;

  cin >> n;

  vector<long long> v(n, 0);

  for(auto &it:v){
    cin >> it;
  }

  long long low = -1;
  long long high = 1e13 + 10;
  //long long high = 10;

  while(high - low > 1){
    long long mid = (low + high) / 2;
    if(ok(v, mid)){
      high = mid;
    }else{
      low = mid;
    }
  }

  cout << high << "\n";

  return 0;
}
