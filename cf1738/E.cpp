#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0) {
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
    b = mult(b, b);
    e >>= 1;
  }

  return p;
}

int comb(const vector<int> &fact, const vector<int> &ifact, int n, int k){
  return mult(fact[n], mult(ifact[k], ifact[n - k]));
}

int main(){
  
  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);

    vector<int> a(n, 0);
    vector<long long> pref(n, 0);
    vector<long long> suff(n, 0);
    vector<int> dp(n + 1, 0);
    vector<int> fact(n + 1, 1);
    vector<int> ifact(n + 1, 1);

    for(int i = 1;i <= n;i++){
      fact[i] = mult(fact[i - 1], i);
    }
    ifact[n] = lgpow(fact[n], MOD - 2);
    for(int i = n - 1;i >= 0;i--){
      ifact[i] = mult(ifact[i + 1], i + 1);
    }

    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2;i <= n;i++){
      dp[i] = add(dp[i - 1], dp[i - 1]);
    }

    for(auto &it:a){
      scanf("%d", &it);
    }

    for(int i = 0;i < (int)a.size();i++){
      pref[i] = a[i] + (i > 0 ? pref[i - 1]:0);
    }
    
    for(int i = (int)a.size() - 1;i;i--){
      suff[i] = a[i] + (i + 1 < (int)a.size() ? suff[i + 1]:0);
    }
    vector<tuple<long long, int, int> > stuff;

    for(int i = 0;i < (int)a.size();i++){
      stuff.push_back(make_tuple(pref[i], i, 0));
      stuff.push_back(make_tuple(suff[i], i - 1, 1));
    }

    sort(stuff.begin(), stuff.end());

    vector<int> combi;
    long long last_value = -1;
    vector<int> running;

    for(auto it:stuff){
      if(get<0>(it) != last_value){
        
        while(!running.empty() && running.back() == 0){
          running.pop_back();
        }
        reverse(running.begin(), running.end());
        while(!running.empty() && running.back() == 1){
          running.pop_back();
        }
        reverse(running.begin(), running.end());
        
        if(!running.empty()){
          int __case = 0;///000011111
          for(int i = 0;i + 1 < (int)running.size();i++){
            if(running[i] > running[i + 1]){
              __case = 1;
              break;
            }
          }
          if(__case == 0){
            int cnt_0 = 0;
            int cnt_1 = 0;
            for(auto it:running){
              cnt_0 += (it == 0);
              cnt_1 += (it == 1);
            }

            int value = 0;
            for(int k = 0;k <= cnt_0 && k <= cnt_1;k++){
               value = add(value, mult(comb(fact, ifact, cnt_0, k), comb(fact, ifact, cnt_1, k)));
            }
            combi.push_back(value);
          }else{
            int cnt_values = 1;
            for(auto it:running){
              cnt_values += (it == 0);
            }
            
            combi.push_back(dp[cnt_values]);
          }
        }

        last_value = get<0>(it);
        running.clear();
      }
      running.push_back(get<2>(it));
    }
    
    while(!running.empty() && running.back() == 0){
      running.pop_back();
    }
    reverse(running.begin(), running.end());
    while(!running.empty() && running.back() == 1){
      running.pop_back();
    }
    reverse(running.begin(), running.end());
    
    if(!running.empty()){
      int __case = 0;///000011111
      for(int i = 0;i + 1 < (int)running.size();i++){
        if(running[i] > running[i + 1]){
          __case = 1;
          break;
        }
      }
      if(__case == 0){
        int cnt_0 = 0;
        int cnt_1 = 0;
        for(auto it:running){
          cnt_0 += (it == 0);
          cnt_1 += (it == 1);
        }
        int value = 0;
        for(int k = 0;k <= cnt_0 && k <= cnt_1;k++){
           value = add(value, mult(comb(fact, ifact, cnt_0, k), comb(fact, ifact, cnt_1, k)));
        }
        combi.push_back(value);
      }else{
        int cnt_values = 1;
        for(auto it:running){
          cnt_values += (it == 0);
        }
      
        combi.push_back(dp[cnt_values]);
      }
    }
    
    int ans = 1;

    for(auto &it:combi){
      ans = mult(ans, it);
    }
    printf("%d\n", ans);
  }

  return 0;
}
