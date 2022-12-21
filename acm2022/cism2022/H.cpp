#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 9;

int add(int a, int b){
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

int lgpow(int b, int e){
  int p = 1;
  while(e){
    if(e & 1){
      p = mult(p, b);
    }
    e >>= 1;
    b = mult(b, b);
  }
  return p;
}

//assumes v is sorted
int calcArrange(const vector<int> &v, const vector<int> &fact, const vector<int> &ifact, int left, int right){
  vector<int> lengths;
  for(int i = left;i <= right;i++){
    if(i == left || v[i] != v[i - 1]){
      lengths.push_back(0);
    }
    lengths.back()++;
  }

  int ans = fact[right - left + 1];
  for(auto it:lengths){
    ans = mult(ans, ifact[it]);
  }
  return ans;
}

int main(){

  int n;
  cin >> n;
  vector<int> v(n + 1);

  for(int i = 1;i <= n;i++){
    cin >> v[i];
  }

  sort(v.begin() + 1, v.end());

  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  vector<int> fact(n + 5, 1);
  for(int i = 1;i < (int)fact.size();i++){
    fact[i] = mult(fact[i - 1], i);
  }

  vector<int> ifact(fact.size(), lgpow(fact.back(), MOD - 2));
  vector<int> inv(ifact.size(), 1);

  for(int i = (int)ifact.size() - 2;i >= 0;i--){
    ifact[i] = mult(ifact[i + 1], i + 1);
  }

  for(int i = 1;i < (int)inv.size();i++){
    inv[i] = mult(ifact[i], fact[i - 1]); 
  }

  vector<int> arrangeFirst(n + 1, 1);

  for(int i = 1;i <= n;i++){
    arrangeFirst[i] = calcArrange(v, fact, ifact, 1, i);
  }

  for(int i = 1;i <= n;i++){
    dp[i] = arrangeFirst[i];
    int arrangeLast = 1;
    int fr = 0;
    int length = 0;
    for(int j = i;j >= 1;j --){
       dp[i] = sub(dp[i], mult(dp[j - 1], arrangeLast));
       if(j == i || v[j] != v[j + 1]){
        fr = 0;
       }
       fr++;
       length++;
       arrangeLast = mult(arrangeLast, length);
       arrangeLast = mult(arrangeLast, inv[fr]);
    }
  }
  
  cout << dp[n];

  return 0;
}
