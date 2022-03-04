#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

inline int add(int a,int b){
  a += b;
  return (a < MOD ? a:a - MOD);
}

inline int mult(int a,int b){
  return 1LL * a * b % MOD;
}

struct inel_t{
  vector<int> sum;

  inel_t(){
    this->sum = vector<int>(3, 0);
  }

  inel_t operator + (const inel_t &other)const{
    inel_t ans;
    ans.sum[0] = add(this->sum[0], other.sum[0]);
    ans.sum[1] = add(this->sum[1], other.sum[1]);
    ans.sum[2] = add(this->sum[2], other.sum[2]);
    return ans;
  }

  inel_t operator * (const inel_t &other)const{
    inel_t ans;
    ans.sum[0] = add(ans.sum[0], mult(this->sum[0], other.sum[0]));
    
    ans.sum[1] = add(ans.sum[1], mult(this->sum[1], other.sum[0]));
    ans.sum[1] = add(ans.sum[1], mult(this->sum[0], other.sum[1]));
    
    ans.sum[2] = add(ans.sum[2], mult(this->sum[2], other.sum[0]));
    ans.sum[2] = add(ans.sum[2], mult(this->sum[1], other.sum[1]));
    ans.sum[2] = add(ans.sum[2], mult(this->sum[1], other.sum[1]));
    ans.sum[2] = add(ans.sum[2], mult(this->sum[0], other.sum[2]));

    return ans;
  }
};

int main(){

  int n, m, k, x, y;
  
  scanf("%d %d %d %d %d", &n, &m, &k, &x, &y);
  
  vector<int> v(m, 0);

  for(auto &it:v){
    scanf("%d", &it);
  }

  vector<vector<inel_t> > dp(1, vector<inel_t>(m, inel_t()));

  for(int i = 0;i < m;i++){
    if(i <= y){
      dp[0][i].sum = {v[i], v[i], v[i]};
    }else{
      dp[0][i].sum = {v[i], 0, 0};
    }
  }


  for(int h = 1;(n >> h);h++){
    dp.push_back(vector<inel_t>(m, inel_t()));

    for(int i = 0;i < m;i++){
      int sum_rest = i;
      for(int j = 0;j < m;j++){
        dp[h][sum_rest] = dp[h][sum_rest] + dp[h - 1][i] * dp[h - 1][j];
        sum_rest = (sum_rest == m - 1 ? 0:sum_rest + 1);
      }
    }
  }

  vector<inel_t> final_dp(m, inel_t());
  final_dp[0].sum = {1, 0, 0};

  for(int h = (int)dp.size() - 1;h >= 0;h--){
    if((n >> h) & 1){
      vector<inel_t> tmp_dp(m, inel_t());
      
      for(int i = 0;i < m;i++){
        int sum_rest = i;
        for(int j = 0;j < m;j++){
          tmp_dp[sum_rest] = tmp_dp[sum_rest] + final_dp[i] * dp[h][j];
          sum_rest = (sum_rest == m - 1 ? 0:sum_rest + 1);
        }
      }
      final_dp.swap(tmp_dp);
    }
  }

  inel_t ans;

  for(int i = 0;i <= x;i++){
    ans = ans + final_dp[i];
  }

  printf("%d\n", ans.sum[k]);

  return 0;  
}
