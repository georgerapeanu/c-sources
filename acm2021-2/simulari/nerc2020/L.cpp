#include <bits/stdc++.h>

using namespace std;

struct node_t {
  int left,  right;
  int min, max;
  int count;
};

const int NMAX = 2e5;
const int QMAX = 2e5;

int n;
node_t tree[NMAX + 5];

class FenwickTree2D{
  int n;
  vector<vector<int> > positions;
  vector<vector<int> > aib;

public:
  
  FenwickTree2D(int n){
    this->positions = vector<vector<int> >(n + 1,vector<int>());
    this->aib = vector<vector<int> >(n + 1,vector<int>());
    this->n = n;
  }

  void prepareUpdate(int x,int y){
    for(int i = x;i;i -= (-i) & i){
      this->positions[i].push_back(y); 
    }
  }

  void prepareQuery(int x,int y){
    for(int i = x;i <= n;i += (-i) & i){
      this->positions[i].push_back(y); 
    }
  }

  void build(){
    for(int i = 1;i <= n;i++){
      sort(positions[i].begin(),positions[i].end());
      positions[i].resize(unique(positions[i].begin(),positions[i].end()) - positions[i].begin());
      aib[i] = vector<int>(positions[i].size() + 1,0);
    }
  }

  void update(int x,int y,int value){
    for(int i = x;i;i -= (-i) & i){
      int startPos = lower_bound(positions[i].begin(),positions[i].end(),y) - positions[i].begin() + 1;
      assert(positions[i][startPos - 1] == y);
      for(int j = startPos;j < (int)aib[i].size();j += (-j) & j){
        aib[i][j] += value;
      }
    }
  }

  int query(int x,int y){
    int ans = 0;
    for(int i = x;i <= n;i += (-i) & i){
      int startPos = lower_bound(positions[i].begin(),positions[i].end(),y) - positions[i].begin() + 1;
      assert(positions[i][startPos - 1] == y);
      for(int j = startPos;j;j -= (-j) & j){
        ans += aib[i][j];
      }
    }
    return ans;
  }
}aib(1);

void build(int nod,int offset){
  if(nod == 0){
    return ;
  }
  build(tree[nod].left,offset);
  build(tree[nod].right,offset + tree[tree[nod].left].count + 1);
  tree[nod].count = tree[tree[nod].left].count + 1 + tree[tree[nod].right].count;
  tree[nod].min = offset;
  tree[nod].max = offset + tree[nod].count - 1;

  aib.prepareUpdate(tree[nod].min,tree[nod].max);
  aib.prepareUpdate(tree[nod].max,tree[nod].min);
}

void dfs(int nod){
  if(nod == 0){
    return ;
  }
  dfs(tree[nod].left);
  dfs(tree[nod].right);
  aib.update(tree[nod].min,tree[nod].max,-2);
  aib.update(tree[nod].max,tree[nod].min,2);
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
  int sgn = 1;
  int ans = 0;
  
  while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }

  if(buff[ind] == '-'){
    sgn = -1;
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

  return ans * sgn;
}

pair<int,int> queries[QMAX + 5];

int main() {
  
  n = i32();

  aib = FenwickTree2D(n);

  map<int,int> to_norm;

  for(int i = 1; i <= n; i++) {
    int l,r,k;
    l = i32();
    r = i32();
    k = i32();
    to_norm[k] = 1; 
    tree[i] = {l,r,0,0};
  }
  
  int last = 0;

  for(auto &it:to_norm){
    it.second = ++last;
  }


  build(1,1);

  int q;
  q = i32();

  for(int i = 1;i <= q;i++){
    int l,r;
    l = i32();
    r = i32();
    map<int,int>::iterator it;
    it = (to_norm.lower_bound(l));
    if(it == to_norm.end()){
      queries[i] = {-1,-1};
      continue;
    }
    l = it->second;
    it = (to_norm.lower_bound(r + 1));
    if(it == to_norm.begin()){
      queries[i] = {-1,-1};
      continue;
    }else{
      it--;
      r = it->second;
    }
    queries[i] = {l,r};
    aib.prepareQuery(l,r);
  }


  aib.build();
  dfs(1);

  for(int i = 1;i <= q;i++){
    if(queries[i].first == -1){
      printf("1\n");
    }else{
      printf("%d\n",aib.query(queries[i].first,queries[i].second) + 1);
    }
  }

  return 0;
}
