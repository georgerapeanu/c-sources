#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;
  cin >> n;

  vector<string> matrix(n);

  int coins = 0;

  for(auto &it:matrix){
    cin >> it;

    for(auto it2:it){
      coins += (it2 == 'C');
    }
  }
  cout << coins << "\n";

  return 0;
}
