#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e3;

int n,k;
int dp[NMAX + 5][NMAX + 5];
int delta[NMAX + 5][10];

string str_digits[] = {
"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"
};

int digits[10];

int main(){

  for(int i = 0;i < 10;i++){
    int digit = 0;
    for(auto it:str_digits[i]){
      digit = (digit << 1) + it - '0';
    }
    digits[i] = digit;
  }

  cin >> n >> k;

  for(int i = 1;i <= n;i++){
    string s;
    cin >> s;

    int digit = 0;

    for(auto it:s){
      digit = (digit << 1) + it - '0';
    }
    
    for(int j = 0;j < 10;j++){
      if((digit & digits[j]) != digit){
        delta[i][j] = -1;
      }else{
        delta[i][j] = __builtin_popcount(digits[j] ^ digit);
      }
    }
  }

  dp[n + 1][0] = 1;

  for(int i = n;i > 0;i--){
    for(int j = 0;j <= k;j++){
      for(int digit = 0;digit < 10;digit++){
        if(delta[i][digit] != -1 && j - delta[i][digit] >= 0){
          dp[i][j] |= dp[i + 1][j - delta[i][digit]];
        }
      }
    }
  }

  if(dp[1][k] == 0){
    cout << -1;
    return 0;
  }

  int x = 1;
  int y = k;

  while(x <= n){
    for(int digit = 9;digit >= 0;digit--){
      if(delta[x][digit] != -1 && dp[x + 1][y - delta[x][digit]]){
        cout << digit;
        y -= delta[x][digit];
        x++;
        break;
      }
    }
  }

  return 0;
}
