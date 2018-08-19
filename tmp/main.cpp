///proof of concept source
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MOD = 1e9 + 7;
int N;

class Int{
   private:
   int val;
   public:
   Int(){
      val = 0;
   }
   Int(int val){
      this->val = val;
   }
   Int operator +(const Int &other)const{
      Int ans(val + other.val);
      if(ans.val >= MOD){
         ans.val -= MOD;
      }
      return ans;
   }

   Int operator *(const Int &other)const{
      Int ans;
      ans.val = 1LL * val * other.val % MOD;
      return ans;
   }

   int toInt(){
      return val;
   }
};

void operator += (Int &a,Int &b){
   a = a + b;
}

Int dp[305][2];

void fix(map<int,int> &tmp,pair<int,int> wut){
    if(wut.first == 1){
        tmp[2] += tmp[1] / 2;
        tmp[1] &= 1;
        if(tmp[1] == 0){
            tmp.erase(1);
        }
        return;
    }
    if(wut.first == 2){
        int a = (tmp.count(wut.first - 1) ? tmp[wut.first - 1] : 0);
        int b = wut.second;
        int t = min(a,b);
        if(t){
            tmp[3] += t;
            tmp[1] -= t;
            tmp[2] -= t;
            if(tmp[1] == 0){
                tmp.erase(1);
            }
            if(tmp[2] == 0){
                tmp.erase(2);
            }
        }
        return;
    }
    int a = (tmp.count(wut.first - 1) ? tmp[wut.first - 1] : 0);
    int b = wut.second;
    int t = min(a,b);
    if(t){
        tmp[wut.first + 1] += t;
        tmp[wut.first] -= t;
        tmp[wut.first - 1] -= t;
        if(tmp[wut.first] == 0){
            tmp.erase(wut.first);
        }
        if(tmp[wut.first] - 1 == 0){
            tmp.erase(wut.first - 1);
        }
    }
    if(tmp[wut.first] > 1){
        t = tmp[wut.first] - 1;
        tmp[wut.first - 2] += t;
        tmp[wut.first - 1] += t;
        tmp[wut.first] = 1;
        fix(tmp,{wut.first - 1,tmp[wut.first - 1]});
        fix(tmp,{wut.first - 2,tmp[wut.first - 2]});
    }
}

vector<int> convert_state(vector<int> &a){
    map<int,int> tmp;
    for(auto it:a){
        tmp[it]++;
    }

    for(auto it:tmp){
        if(it.second){
            fix(tmp,it);
        }
    }

    vector<int> ans;
    for(auto it:tmp){
        ans.push_back(it.first - 1);
    }

    return ans;
}

int n;
vector<int> v;

int main() {
    cin >> n;
    for(int i = 0;i < n;i++){
       int x = 0;
       cin >> x;
       v.push_back(x);
       vector<int> con = convert_state(v);
       memset(dp,0,sizeof(dp));

       dp[0][0] = con[0] / 2;
       dp[0][1] = 1;

       for(int i = 1;i < (int)con.size();i++){
            dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
            dp[i][0] = dp[i - 1][0] * Int((con[i] - con[i - 1]) / 2) + dp[i - 1][1] * Int((con[i] - con[i - 1] - 1) / 2);
       }

       cout << (dp[(int)con.size() - 1][0] + dp[(int)con.size() - 1][1]).toInt() << "\n";
    }
    return 0;
}
