#include <iostream>
#include "erinaceida.h"

using namespace std;

int main(){
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;
  vector<int> X(N, 0);
  vector<int> Y(N, 0);
  vector<int> Z(N, 0);

  for(int i = 0;i < N;i++){
    cin >> X[i] >> Y[i] >> Z[i];
  }
  
  pair<int, int> ans = collectFruits(N, X, Y, Z);

  cout << ans.first << " " << ans.second << "\n";


  return 0;
}
