#include <bits/stdc++.h>
using namespace std;

typedef long long int64;

void fixAns(vector<int64> &ans,vector<int> &tp){
  vector<int> order;
  for(int i = 0;i < (int)ans.size();i++){
    order.push_back(i);
  }
  sort(order.begin(),order.end(),[&](int a,int b){
    return tp[a] < tp[b];
  });
  vector<int64> tmp_ans;
  vector<int> tmp_tp;
  for(auto it:order){
    tmp_ans.push_back(ans[it]);
    tmp_tp.push_back(tp[it]);
  }
  
  ans = tmp_ans;
  tp = tmp_tp;
}

void printAns(vector<int64> ans){
  sort(ans.begin(),ans.end());
  for(auto it:ans){
    printf("%lld ",it);
  }
  exit(0);
}

int64 mult(int64 a,int64 b,int64 mod){
  int64 ans = 0;
  while(b){
    if(b & 1){
      ans += a;
      if(ans >= mod){
        ans -= mod;
      }
    }
    a += a;
    if(a >= mod){
      a -= mod;
    }
    b >>= 1;
  }
  return ans;
}

int64 lgpow(int64 b,int64 e,int64 mod){
  int64 p = 1;

  while(e){
    if(e & 1){
      p = mult(p,b,mod);
    }
    b = mult(b,b,mod);
    e >>= 1;
  }

  return p;
}

bool is_prime(int64 value){
  if(value < 2){
    return false;
  }

  for(auto it:{2,3,5,7,11,13,17,19,23,29,31,37}){
    if(value <= it){
      return true;
    }
    if(lgpow(it,value - 1,value) != 1){
      return false;
    }
  }
  return true;
}

vector<int64> filter_unique(vector<int64> v){
  vector<int64> ans;
  int64 last = -1;
  for(auto it:v){
    if(last == it && (ans.empty() || ans.back() != it)){
      ans.push_back(it);
    }
    last = it;
  }
  return ans;
}

int main(){
  const int VMAX = 1e6;
  vector<int> primes;
  vector<bool> __is_prime(VMAX + 1,true);
  
  __is_prime[0] = __is_prime[1] = false;

  for(int i = 2;i <= VMAX;i++){
    if(__is_prime[i]){
      primes.push_back(i);
      for(int j = 2 * i;j <= VMAX;j += i){
        __is_prime[j] = false;
      }
    }
  }

  int n,k;
  vector<int64> values;
  vector<bool> is_pure;
  vector<int64> lowest_prime;
  
  scanf("%d %d",&n,&k);

  values = vector<int64>(n,0);
  is_pure = vector<bool>(n,false);
  lowest_prime = vector<int64>(n,0);

  for(auto &it:values){
    scanf("%lld",&it);
  }

  vector<int64> base_primes;

  for(int i = 0;i < n;i++){
    int cnt_p = 0;
    int64 it = values[i];
    for(auto p:primes){
      if(1LL * p * p > it){
        break;
      }
      if(it % p == 0){
        cnt_p++;
        if(lowest_prime[i] == 0){
          lowest_prime[i] = p;
        }
        while(it % p == 0){
          it /= p;
        }
      }
    }
    if((it > 1 && it <= VMAX) || is_prime(it)){
      cnt_p++;
      if(lowest_prime[i] == 0){
        lowest_prime[i] = it;
      }
    }else if(it > 1){
      int64 tmp = sqrt(it);
      if(tmp * tmp == it){
        cnt_p++;
        if(lowest_prime[i] == 0){
          lowest_prime[i] = tmp;
        }
      }
    }


    if(cnt_p == 1){
      is_pure[i] = true;
      base_primes.push_back(lowest_prime[i]);
    }
  }
  sort(base_primes.begin(),base_primes.end());
  
  base_primes = filter_unique(base_primes);
  
  map<int64,int> to_norm;


  for(int i = 0;i < (int)base_primes.size();i++){
    to_norm[base_primes[i]] = i;
  }


  if((int)base_primes.size() * 2 <= k){
    vector<int64> ans;
    vector<int> tp;
    vector<int> cnt((int)base_primes.size(),0);
    vector<int64> composite;
    for(int i = 0;i < n;i++){
      if(is_pure[i] && to_norm.count(lowest_prime[i]) && cnt[to_norm[lowest_prime[i]]] < 2){
        cnt[to_norm[lowest_prime[i]]]++;
        ans.push_back(values[i]);
        tp.push_back(lowest_prime[i]);
        continue;
      }
      int64 tmp = values[i];
      for(auto it:base_primes){
        while(tmp % it == 0){
          tmp /= it;
        }
      }
      if(tmp == 1){
        composite.push_back(values[i]);
      }
    }
    fixAns(ans,tp);
    for(auto it:composite){
      ans.push_back(it);
    }
    if((int)ans.size() < k){
      printAns({0});
    }
    ans.resize(k);
    printAns(ans);
  }else{
    vector<int64> ans;
    vector<int> tp;
    vector<int> cnt((int)base_primes.size(),0);
    int best_cnt = 1e9;
    int best_pos = -1;
    for(int i = 0;i < n;i++){
      if(is_pure[i] && to_norm.count(lowest_prime[i]) && cnt[to_norm[lowest_prime[i]]] < 2){
        cnt[to_norm[lowest_prime[i]]]++;
        ans.push_back(values[i]);
        tp.push_back(to_norm[lowest_prime[i]]);
        continue;
      }
      int64 tmp = values[i]; 
      int cnt = 0;
      for(auto it:base_primes){
        bool has = false;
        while(tmp % it == 0){
          tmp /= it;
          has = true;
        }
        cnt += has;
      }
      if(tmp == 1 && cnt < best_cnt){
        best_cnt = cnt;
        best_pos = i;
      }
    }
    fixAns(ans,tp);
    if((int)ans.size() % 2 == k % 2){
      while((int)ans.size() > k){
        ans.pop_back();
      }
      printAns(ans);
    }else if(best_pos != -1){
      vector<bool> is_special((int)base_primes.size(),false);
      for(auto it:base_primes){
        int64 tmp = values[best_pos];
        if(tmp % it == 0){
          is_special[to_norm[it]] = true;
        }
      }
      deque<int64> sorted_ans;
      deque<int64> sorted_tp;
      for(int i = 0;i < (int)ans.size();i++){
        if(is_special[tp[i]]){
          sorted_ans.push_front(ans[i]);
          sorted_tp.push_front(tp[i]);
        }else{
          sorted_ans.push_back(ans[i]);
          sorted_tp.push_back(tp[i]);
        }
      }
      while(sorted_tp.empty() == false && is_special[sorted_tp.back()] == 0 && (int)sorted_ans.size() > k){
        sorted_tp.pop_back();
        sorted_tp.pop_back();
        sorted_ans.pop_back();
        sorted_ans.pop_back();
      }

      if((int)sorted_ans.size() > k){
        printAns({0});
      }
      sorted_ans.push_back(values[best_pos]);
      ans.clear();
      for(auto it:sorted_ans){
        ans.push_back(it);
      }
      printAns(ans);
    }else{
      printAns({0});
    }
  }

  return 0;
}
