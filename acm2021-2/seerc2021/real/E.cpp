#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 5;

struct FenwickTree{
  int n;
  vector<int> aib;

  FenwickTree(){
    ;
  }

  FenwickTree(int n){
    this->n = n;
    this->aib = vector<int>(n + 1,-inf);
  }

  void update(int pos,int val){
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] = max(aib[pos], val);
    }
  }

  int query(int pos){
    int ans = -inf;

    for(;pos;pos -= (-pos) & pos){
      ans = max(ans, aib[pos]);
    }
    return ans;
  }
};

struct FenwickTree2D{
  int n;
  vector<FenwickTree> aib;
  vector<vector<int>> coords;
  
  FenwickTree2D(int n){
    this->n = n;
    this->coords = vector<vector<int> >(n + 1,vector<int>());
    this->aib = vector<FenwickTree>(n + 1);
  }

  void fakeUpdate(int x,int y){
    for(int i = x;i <= n;i += (-x) & x){
      coords[i].push_back(y);
    }
  }

  void init(){
    for(int i = 1;i <= n;i++){
      sort(coords[i].begin(),coords[i].end());
      coords[i].resize(unique(coords[i].begin(),coords[i].end()) - coords[i].begin());
      aib[i] = FenwickTree(coords[i].size());
    }
  }

  int ind(int x,int y){
    return lower_bound(coords[x].begin(),coords[x].end(),y + 1) - coords[x].begin();
  }
  

  void update(int x,int y,int value){
    for(int i = x;i <= n;i += (-i) & i){
      aib[i].update(ind(i, y), value);
//      printf("====subupdate on %d %d with %d\n",i,ind(i,y),value);
    }
  }

  int query(int x,int y){
    int ans = -inf;

    for(int i = x;i;i -= (-i) & i){
      ans = max(ans, aib[i].query(ind(i, y)));
//      printf("=====subquery on %d %d is %d\n",i,ind(i,y), aib[i].query(ind(i,y)));
    }

    return ans;
  }

};

int main(){
    
  int n, m;
  vector<int> a;
  vector<int> b;

  scanf("%d %d",&n,&m);

  a = vector<int>(n,0);
  b = vector<int>(m,0);

  for(auto &it:a){
    scanf("%d",&it);
  }

  for(auto &it:b){
    scanf("%d",&it);
  }

  a.push_back(inf + 1);
  n++;

  vector<pair<int,int> > together;

  for(int i = 0;i < n;i++){
    together.push_back({a[i],i});
  }

  for(int i = 0;i < m;i++){
    together.push_back({b[i],-1});
  }

  sort(together.begin(),together.end());

  int cnt_a = 0;
  int cnt_b = 0;

  vector<int> coef(n,0);
  for(auto it:together){
    if(it.second == -1){
      cnt_b++;
    }else{
      cnt_a++;
      a[it.second] = cnt_a;
      coef[it.second] = cnt_b - it.second;
    }
  }

  FenwickTree2D aib(n + 1);

  aib.fakeUpdate(1, -1);
  for(int i = 0;i < n;i++){
    aib.fakeUpdate(1 + a[i], coef[i]);
    aib.fakeUpdate(1 + a[i], coef[i] + 1);
  }

  aib.init();
  aib.update(1,-1,0);
  vector<int> dp(n + 1, 0);

  //printf("plm %d\n",aib.ind(4,0));

  for(int i = 0;i < n;i++){
    //printf("debug %d %d\n",a[i], coef[i]);
  }

  for(int i = 0;i < n;i++){
    dp[i + 1] = aib.query(a[i] + 1, coef[i] + 1);
    //printf("query on %d %d is %d\n",a[i] + 1,coef[i] + 1,dp[i + 1]);
    if(dp[i + 1] == -inf){
      continue;
    }
    dp[i + 1]++;
    aib.update(a[i] + 1, coef[i], dp[i + 1]);
    //printf("update %d %d with %d\n",a[i] + 1,coef[i],dp[i + 1]);
  }


  //for(auto it:dp){
   // printf("debug %d\n",it);
  //}


  
  if(dp[n] < 0){
    printf("-1\n");
    return 0;
  }

  printf("%d\n", n - dp[n]);

    return 0;
}
