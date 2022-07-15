#include <bits/stdc++.h>

using namespace std;

struct node_t{
  long long depth; /// depthul minim din subarbore
  long long cnt; /// suma valorilor nodurilor care au depth=minim
  long long lazy ; ///lazy

  node_t(){
    cnt = depth = 0;
    lazy = 0;
  }

  node_t(int depth, long long cnt){
    this->depth = depth;
    this->cnt = cnt;
    this->lazy = 0;
  }

  node_t operator + (const node_t &other)const{ /// operatia de join
    node_t ans;
    ans.lazy = 0;
    if(other.depth < this->depth){
      ans.cnt = other.cnt;
      ans.depth = other.depth;
    }else if(other.depth == this->depth){
      ans.cnt = other.cnt + this->cnt;
      ans.depth = this->depth;
    }else{
      ans.cnt = this->cnt;
      ans.depth = this->depth;
    }
    return ans;
  }

  void propagate(long long lazy){ ///aplica lazy pe un nod
    this->lazy += lazy; ///aplica lazy pe lazy
    this->depth += lazy; /// aplica lazy-ul pe depthu minim
  }

  void debug(){
    cerr << depth << " " << cnt << " " << lazy << "\n";
  }
};

class SegmentTree{
  int n;
  vector<node_t> aint;

  void build(int nod,int st,int dr, const vector<int> &v){
    if(st == dr){
      aint[nod] = node_t(0,v[st]);
      return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2, st, mid, v);
    build(nod * 2 + 1, mid + 1, dr, v);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void propagate(int nod, int st, int dr){
    if(st == dr || aint[nod].lazy == 0){
      return ;
    }
    aint[nod * 2].propagate(aint[nod].lazy);
    aint[nod * 2 + 1].propagate(aint[nod].lazy);
    aint[nod].lazy = 0;
  }

  void update_set(int nod, int st, int dr, int pos, int value){
    propagate(nod, st, dr);

    if(dr < pos || st > pos){
      return ;
    }
    
    if(st == dr){
      aint[nod].cnt = value;
      return ;
    }

    int mid = (st + dr) / 2;

    update_set(nod * 2, st, mid, pos, value);
    update_set(nod * 2 + 1, mid + 1, dr, pos, value);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void update_add(int nod, int st, int dr, int l, int r, int value){
    propagate(nod, st, dr);

    if(dr < l || st > r){
      return ;
    }

    if(l <= st && dr <= r){
      aint[nod].propagate(value);
      return ;
    }

    int mid = (st + dr) / 2;

    update_add(nod * 2, st, mid, l, r, value);
    update_add(nod * 2 + 1, mid + 1, dr, l, r, value);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  public:

  SegmentTree(const vector<int> &v){
    this->n = (int)v.size() - 1;
    this->aint = vector<node_t>(4 * n + 5, node_t());
    this->build(1, 1, n, v);
  }

  void update_add(int l, int r, int x){
    //cerr << "add" <<  l << " " << r << " " << x << "\n";
    update_add(1, 1, n, l, r, x);
  }

  void update_set(int pos, int value){
    //cerr << "set " << pos << " to " << value << "\n";
    update_set(1, 1, n, pos, value);
  }

  node_t get_top(){
    return aint[1];
  }

  void debug(){
    for(int nod = 1;nod < (int)aint.size() && aint[nod].cnt > 0;nod++){
      cerr << "nod " << nod << " is:\n";
      aint[nod].debug();
    }
    cerr << "===================================================================" << endl;
  }
};

void dfs(int nod, int tata, const vector<vector<int> > &graph, vector<int> &left, vector<int> &right, int &last_value){
  left[nod] = ++last_value;
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    dfs(it, nod, graph, left, right, last_value);
  }
  right[nod] = last_value;
}

int main(){

  int n, q;

  scanf("%d %d", &n, &q);
  
  vector<int> v(n + 1, 0);
  vector<int> status(n + 1, 0);
  vector<vector<int> > graph(n + 1, vector<int>());
  vector<int> left(n + 1, 0);
  vector<int> right(n + 1, 0);
  int last_euler_id = 0;

  for(int i = 1;i < n;i++){
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  for(int i = 1;i <= n;i++){
    scanf("%d", &v[i]);
  }

  dfs(1, 0, graph, left, right, last_euler_id);
  vector<int> aint_v(n + 1, 0);
  for(int i = 1;i <= n;i++){
    aint_v[left[i]] = v[i];
  }
  SegmentTree aint(aint_v);
  
  /*
  for(int i = 1;i <= n;i++){
    cerr << left[i] << " " << right[i] << "\n";
  }
  */

  while(q--){
    int t;
    scanf("%d", &t);

    if(t == 1){
      int nod, value;
      scanf("%d %d", &nod, &value);
      aint.update_set(left[nod], value);
    }else{
      int y;
      scanf("%d", &y);
      aint.update_add(left[y], right[y], (status[y] == 1 ? -1:1));
      status[y] ^= 1;
    }
    printf("%lld\n", aint.get_top().cnt); /// ar fi trebuit sa verific ca aint.get_top().depth e 0
  //  aint.debug();
  }
  
  return 0;
}
