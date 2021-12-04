#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int NMAX = 300;
const int VMAX = 300;

class ModularInt{
  int mod;
 
public:
  
  int a;
  
  ModularInt(){
    ;
  }

  ModularInt(int mod){
    this->a = 0;
    this->mod = mod;
  }

  ModularInt(int a,int mod){
    this->a = a;
    this->mod = mod;
  }

  ModularInt operator + (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = this->a + other.a;
    if(ans.a >= mod){
      ans.a -= mod;
    }
    return ans;
  }

  ModularInt operator - (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = this->a - other.a;
    if(ans.a < 0){
      ans.a += mod;
    }

    return ans;
  }

  ModularInt operator * (const ModularInt &other)const{
    ModularInt ans;
    ans.mod = this->mod;
    ans.a = 1LL * this->a * other.a % mod;
    return ans;
  }
};


int main(){
  int n;
  scanf("%d",&n);

  int smax = n * VMAX;
  
  vector<ModularInt> dp(smax + 1,ModularInt(0,MOD));
  vector<ModularInt> rucsac(smax + 1,ModularInt(0,MOD));


  dp[0] = ModularInt(1,MOD);
  rucsac[0] = ModularInt(1,MOD);
  int sum = 0;
  for(int i = 1;i <= n;i++){
    int val;
    scanf("%d",&val);
    sum += val;

    for(int j = smax;j >= 0;j--){
      dp[j] = dp[j] * ModularInt(2,MOD);
      if(j >= val){
        dp[j] = dp[j] + dp[j - val];
        rucsac[j] = rucsac[j] + rucsac[j - val];
      }
    }
  }

  ModularInt ans(1,MOD);

  for(int i = 1;i <= n;i++){
    ans = ans * ModularInt(3,MOD);
  }

  for(int i = 0;i <= sum;i++){
    if(sum - i <= i){
      ans = ans - ModularInt(3,MOD) * dp[i]; 
    }
    if(sum - i == i){
      ans = ans + ModularInt(3,MOD) * rucsac[i];  
    }
  }

  printf("%d\n",ans.a);

  return 0;
}
