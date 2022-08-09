#include <bits/stdc++.h>

using namespace std;

/// u->v
/// to calculate with set=0 -> -sum((n - size[v])*size[v]*value[u<->v])
/// to remove duplicates
/// 1->lca ->u,v
///we want for each edge x->y from 1 to lca to calculate (n-size(y))*value(x<->y)
///we want for each edge which is not from 1 to u or 1 to v to calculate size(y) * value(x<->y)
///total_sum(size*value) - 2 * sum(size*value from 1 to lca) + n * sum(value from 1 to lca) - sum(size*value from lca to u) - sum(size*value from lca to v)
/// total_size_value + n * value.query(euler_left[lca]) - size_value.query(euler_left[u]) - size_value.query(euler_left[v])

const int MOD = 1e9 + 7;

int add(int a ,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}


///0 indexed
class FenwickTree{
  int n;
  vector<int> aib;
  
public:

  FenwickTree(int n){
    this->n = n;
    this->aib = vector<int>(n + 1, 0);
  }

  void update(int pos, int value){
    //printf("%p update %d with %d\n", this, pos, value);
    pos++;
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] = add(aib[pos], value);
    }
  }

  int query(int pos) const {
    pos++;
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
      ans = add(ans, aib[pos]);
    }
    return ans;
  }
};

void predfs(const vector< vector<pair<int, int>> > &graph, 
            vector<int> &lvl, 
            vector<int>& weight, 
            vector< vector<int> > &fathers,
            vector<int>& father_cost,
            vector<int>& euler_left,
            vector<int>& euler_right,
            int& euler_index,
            int nod, 
            int father){

  euler_left[nod] = euler_index++;
  lvl[nod] = 1 + lvl[father];
  fathers[0][nod] = father;
  weight[nod] = 1;

  for(auto it:graph[nod]){
    if(it.first == father){
      continue;
    }
    father_cost[it.first] = it.second;
    predfs(graph, lvl, weight, fathers, father_cost, euler_left, euler_right, euler_index, it.first, nod);
    weight[nod] += weight[it.first];
  }
  euler_right[nod] = euler_index - 1;
}

void setupAIBs(const int n,
               const vector<int>& weight,
               const vector<int>& father_cost,
               const vector<int>& euler_left,
               const vector<int>& euler_right,
               FenwickTree& calculate_set_aib,
               FenwickTree& calculate_sum_aib,
               FenwickTree& calculate_sum_size_aib){
  for(int i = 1;i <= n;i++){
    calculate_set_aib.update(euler_left[i], mult(mult(n - weight[i], weight[i]),father_cost[i]));
    calculate_set_aib.update(euler_right[i] + 1, sub(0, mult(mult(n - weight[i], weight[i]),father_cost[i])));
    calculate_sum_aib.update(euler_left[i], father_cost[i]);
    calculate_sum_aib.update(euler_right[i] + 1, sub(0, father_cost[i]));
    calculate_sum_size_aib.update(euler_left[i], mult(father_cost[i], weight[i]));
    calculate_sum_size_aib.update(euler_right[i] + 1, sub(0, mult(father_cost[i], weight[i])));
  }
}

int calculateInitialCost(const int n,
                        const vector<int>& weight,
                        const vector<int>& father_cost){
  int ans = 0;

  for(int i = 1;i <= n;i++){
    ans = add(ans, mult(mult(weight[i], sub(n, weight[i])), father_cost[i]));
  }

  return ans;
}

int calculateInitialSizeValueSum(const int n, const vector<int>& weight, const vector<int>& father_cost){
  int ans = 0;

  for(int i = 1;i <= n;i++){
    ans = add(ans, mult(weight[i], father_cost[i]));
  }

  return ans;
  
}

void setupLCA(const int n, vector<vector<int> > &fathers){
  for(int h = 1;h < (int)fathers.size();h++){
    for(int i = 1;i <= n;i++){
      fathers[h][i] = fathers[h - 1][fathers[h - 1][i]];
    }
  }
}

int getLCA(const vector<vector<int> > &fathers, const vector<int> &lvl, int x, int y){
  if(lvl[x] > lvl[y]){
    swap(x, y);
  }
  
  for(int h = (int)fathers.size() - 1; h >= 0; h--){
    if((lvl[y] - lvl[x]) >> h){
      y = fathers[h][y];
    }
  }

  if(x == y){
    return x;
  }

  for(int h = (int)fathers.size() - 1; h >= 0; h--){
    if(fathers[h][x] != fathers[h][y]){
      x = fathers[h][x];
      y = fathers[h][y];
    }
  }

  return fathers[0][x];
}

void update(const int n,
            int& cost, 
            int& sum_size_value,
            const vector<int>& lvl, 
            const vector<int>& weight, 
            vector<int>& father_cost,
            const vector<int>& euler_left, 
            const vector<int>& euler_right, 
            FenwickTree& calculate_set_aib, 
            FenwickTree& calculate_sum_value_aib, 
            FenwickTree& calculate_sum_value_size_aib, 
            int x, 
            int y ,
            int z){

  if(lvl[x] > lvl[y]){
    swap(x, y);
  }
  
  int edge_weight, delta;

  edge_weight = mult(n - weight[y], weight[y]);
  delta = mult(edge_weight, sub(z, father_cost[y]));
  calculate_set_aib.update(euler_left[y], delta);
  calculate_set_aib.update(euler_right[y] + 1, sub(0, delta));

  cost = add(cost, delta);

  delta = sub(z, father_cost[y]);
  calculate_sum_value_aib.update(euler_left[y], delta);
  calculate_sum_value_aib.update(euler_right[y] + 1, sub(0, delta));
  

  edge_weight = weight[y];
  delta = mult(edge_weight, sub(z, father_cost[y]));
  calculate_sum_value_size_aib.update(euler_left[y], delta);
  calculate_sum_value_size_aib.update(euler_right[y] + 1, sub(0, delta));
  
  sum_size_value = add(sum_size_value, delta);

  father_cost[y] = z;
}
int query(const int n,
          const int cost, 
          const int sum_size_value,
          const vector< vector<int> >& fathers, 
          const vector<int>& lvl, 
          const vector<int>& euler_left,
          const vector<int>& euler_right,
          const FenwickTree& calculate_set_aib,
          const FenwickTree& calculate_sum_value_aib,
          const FenwickTree& calculate_sum_size_value_aib,
          int u, 
          int v){
  int lca = getLCA(fathers, lvl, u, v);
  int sum = 0;
  int lca_value;

  lca_value = calculate_set_aib.query(euler_left[lca]);
  sum = add(sum, sub(calculate_set_aib.query(euler_left[u]), lca_value));
  sum = add(sum, sub(calculate_set_aib.query(euler_left[v]), lca_value));

  //printf("data %d %d %d %d %d %d %d %d %d\n", u, v, lca, euler_left[u], euler_right[u], euler_left[v], euler_right[v], euler_left[lca], euler_right[lca]);
  //printf("first stage %d\n", sum);

  int l = lvl[u] + lvl[v] - 2 * lvl[lca];

  //printf("sum_size_value is %d\n", sum_size_value);
  //printf("calculate_size_value lca is %d\n", calculate_sum_size_value_aib.query(euler_left[lca]));
  //printf("calculate_size_value u is %d\n", calculate_sum_size_value_aib.query(euler_left[u]));
  //printf("calculate_size_value v is %d\n", calculate_sum_size_value_aib.query(euler_left[v]));
  sum = add(sum, mult(sum_size_value, l));
  sum = add(sum, mult(mult(n, calculate_sum_value_aib.query(euler_left[lca])), l));
  sum = sub(sum, mult(calculate_sum_size_value_aib.query(euler_left[u]), l));
  sum = sub(sum, mult(calculate_sum_size_value_aib.query(euler_left[v]), l));
  //printf("second stage %d\n", sum);

  return sub(cost, sum);
}

int main(){
  freopen("zelda.in", "r", stdin);
  freopen("zelda.out", "w", stdout);
  int n;
  
  scanf("%d", &n);

  ///graph costs will not be mantained throughout the updates
  vector<vector<pair<int, int> > > graph(n + 1, vector<pair<int, int>>());
  vector<int> lvl(n + 1, 0);
  vector<int> weight(n + 1, 0);
  vector<int> father_cost(n + 1, 0);
  vector<int> euler_left(n + 1, 0);
  vector<int> euler_right(n + 1, 0);
  FenwickTree calculate_set_aib(n + 1);
  FenwickTree calculate_sum_value_aib(n + 1);
  FenwickTree calculate_sum_size_value_aib(n + 1);

  int lg = 0;

  while(n >> lg){
    lg++;
  }
  
  vector<vector<int> > fathers(lg + 1, vector<int>(n + 1, 0));
  for(int i = 1;i < n;i++){
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    graph[x].push_back({y, z});
    graph[y].push_back({x, z});
  }

  int euler_index = 0;
  predfs(graph, lvl, weight, fathers, father_cost, euler_left, euler_right, euler_index, 1, 0);

  setupAIBs(n,  weight, father_cost, euler_left, euler_right, calculate_set_aib, calculate_sum_value_aib, calculate_sum_size_value_aib);
  setupLCA(n, fathers);
  int cost = calculateInitialCost(n, weight, father_cost);
  int sum_size_value = calculateInitialSizeValueSum(n, weight, father_cost);

  int q;

  scanf("%d", &q);

  while(q--){
   int t, x, y;

   scanf("%d %d %d", &t, &x, &y);

   if(t == 0){
    int z;
    scanf("%d", &z);
    update(n, cost, sum_size_value, lvl, weight, father_cost, euler_left, euler_right, calculate_set_aib, calculate_sum_value_aib, calculate_sum_size_value_aib, x, y ,z);
   }else {
    printf("%d\n", query(n, cost, sum_size_value, fathers, lvl, euler_left, euler_right, calculate_set_aib, calculate_sum_value_aib, calculate_sum_size_value_aib, x, y));
   }
  }


  return 0;
}
