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


vector<int> convert_state(vector<int> &a){
    vector<int> ans;
   map<int, int> hs;
    for(int i = 0;i < (int)a.size();i++) {
        hs[a[i]]++;
        while (1) {
            int found = 0;
            for (pair<int,int> e : hs) {
                int x = e.first;
                int y = e.second;
                if (y > 1) {
                    if (x == 1) {
                        hs[x] -= 2;
                        hs[x + 1]++;
                    }
                    else {
                        hs[x] -= 2;
                        hs[max(1, x - 2)]++;
                        hs[x + 1]++;
                    }
                    found = 1;
                }
                else if (y > 0 && hs.count(x - 1) && hs[x - 1] > 0) {
                    hs[x]--;
                    hs[x - 1]--;
                    hs[x + 1]++;
                    found = 1;
                }
            }
            map<int, int> nhs;
            for (pair<int,int> e : hs) {
                if (e.second) nhs[e.first] = e.second;
            }
            hs = nhs;
            if (!found) break;
        }
        int m = 0;
    }
    for (pair<int,int> e : hs) {
       ans.push_back(e.first - 1);
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
