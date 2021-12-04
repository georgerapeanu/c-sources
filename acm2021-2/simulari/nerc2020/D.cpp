#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int KMAX = 8;

int n;
string s;
int tag[NMAX + 5];
int mask[NMAX + 5];
int mask_popcount[NMAX + 5];
int dp[KMAX][1 << KMAX];

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
      cin >> s;
      for(auto it:s){
        tag[i] <<= 1;
        tag[i] |= (it == 'R');
      }
    }

    for(int i = 1;i <= n;i++){
      for(int j = i + 1;j <= n && j <= i + KMAX;j++){
        if(j - i <= KMAX - __builtin_popcount(tag[i] ^ tag[j])){
          mask[i] |= 1 << (j - i - 1);
          mask_popcount[i]++;
        }
      }
    }

    for(int conf = 0;conf < (1 << KMAX);conf++){
      dp[0][conf] = (conf & 1);
    }

    for(int i = 1,l = 1,p = 0;i <= n;i++,l = (l == 7 ? 0:l + 1),p = (p == 7 ? 0:p + 1)){
      for(int conf = 0;conf < (1 << KMAX);conf++){
        int state = !(__builtin_popcount(mask[i] & conf) == mask_popcount[i]);
        int new_conf = ((conf << 1) | state) & ((1 << KMAX) - 1);
        dp[l][conf] = dp[p][new_conf];
      }
      printf("%d",2 - dp[l][255]);
    }




    return 0;
}
