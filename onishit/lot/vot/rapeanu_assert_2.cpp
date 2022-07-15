#include <cassert>
#include <vector>
#include <algorithm>
#include "vote.h"

using namespace std;

int add(int a, int b, int mod){
  a += b;
  if(a >= mod){
    a -= mod;
  }
  return a;
}

int mult(int a, int b, int mod){
  return (1LL * a * b) % mod;
}

int lgpow(int b, int e, int mod){
  int ans = 1;

  while(e){
    if(e & 1){
      ans = mult(ans, b, mod);
    }
    e >>= 1;
    b = mult(b, b, mod);
  }

  return ans;
}

vector<int> fact;
vector<int> ifact;

int comb(int n, int k, int mod){
  assert(0 <= k && k <= n);

  return mult(fact[n], mult(ifact[k], ifact[n - k], mod) , mod);
}

///[l, r)
void compute(int &n, int &m, int mod, int h, int l, int r, const vector<vector<int> > &voturi, vector<int> &answer, vector<int> &dp){
  if(l >= r){
    return ;
  }
  if(h >= m){
    int sum_dp = 0;
    for(int i = 1;i < (int)dp.size();i++){
      sum_dp = add(sum_dp, mult(dp[i], comb(r - l - 1, i -  1, mod), mod), mod); 
    }
    for(int i = l;i < r;i++){
      answer[i] = sum_dp;
    }
    return ;
  }

  int split = r;

  for(int i = l;i < r;i++){
    if(voturi[i][h] == 1){
      split = i;
      break;
    }
  }
  
  vector<int> fst(split - l + 1, 0);
  vector<int> snd(r - split + 1, 0);

  for(int total = 0;total <= r - l;total++){
    for(int i = max(0, total - r + split);i <= split - l && i <= total;i++){
      int j = total - i;
      if(i > j){
        fst[i] = add(fst[i], mult(dp[total], comb(r - split, j, mod), mod), mod);
      }else{
        snd[j] = add(snd[j], mult(dp[total], comb(split - l, i, mod), mod), mod);
      }
    }
  }

  compute(n, m, mod, h + 1, l, split, voturi, answer, fst);
  compute(n, m, mod, h + 1, split, r, voturi, answer, snd);
}

vector<int> waysToWin(int N, int M, int MOD, vector<vector<int> > voturi){
  assert(1 <= N && N <= 20);
  assert(1 <= M && M <= 40);
  assert((int)voturi.size() == N);

  for(auto it:voturi){
    assert(it.size() == M);
    for(auto it2:it){
      assert(0 <= it2 && it2 <= 1);
    }
  }


  fact = vector<int>(N + 1, 1);
  ifact = vector<int>(N + 1, 1);

  for(int i = 1;i <= N;i++){
    fact[i] = mult(i, fact[i - 1], MOD);
  }

  ifact[N] = lgpow(fact[N], MOD - 2, MOD);

  for(int i = N - 1;i >= 0;i--){
    ifact[i] = mult(ifact[i + 1], i + 1, MOD);
  }

  vector<int> order;
  for(int i = 0;i < N;i++){
    order.push_back(i);
  }

  sort(order.begin(), order.end(), [&](int a, int b){
    return voturi[a] < voturi[b];
  });

  vector<vector<int> > new_votes;

  for(auto it:order){
    new_votes.push_back(voturi[it]);
  }

  vector<int> answer(N, 0);
  vector<int> init_dp(N + 1, 1);
  compute(N, M, MOD, 0, 0, N, new_votes, answer, init_dp);  
  vector<int> real_answer(N, 0);

  for(int i = 0;i < N;i++){
    real_answer[order[i]] = answer[i];
  }

  return real_answer;  
}
