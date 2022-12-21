#include <bits/stdc++.h>

using namespace std;

int dp[1000];
int ant[1000];

int main(){

  dp[0] = 0;

  for(int i = 1;i < 1000;i++){
    int ci = i;
    while(ci){
      if(ci % 10){
        dp[i] |= (!dp[i - (ci % 10)]);
        if(!dp[i - (ci % 10)]){
          ant[i] = (ci % 10);
        }
      }
      ci /= 10;
    }
  }

  int value;
  cin >> value;

  int win = 0;
  int move = -1;

  if(value < 1000){
    win = dp[value];
    move = ant[value];
  }else {
    win = (value % 10 != 0);
    move = value % 10;
  }

  if(win == 0){
    cout << 2 << "\n";
  }else{
    cout << 1 << "\n" << move << "\n";
  }

  return 0;
}
