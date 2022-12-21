#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;

  cin >> n;

  int next_ball = 1;
  vector<int> balls;

  for(int i = 1;i <= n;i++){
    int value;
    cin >> value;

    while(next_ball <= value){
      balls.push_back(next_ball);
      next_ball++;
    }
    if(balls.empty() || value != balls.back()){
      cout << "Cheater";
      return 0;
    }
    balls.pop_back();
  }

  cout << "Not a proof";

  return 0;
}
