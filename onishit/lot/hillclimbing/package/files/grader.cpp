#include <iostream>
#include "cetatuie.h"

using namespace std;

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  
  while(t--){
    int n;
    long long k;
    cin >> n >> k;
    int* v = new int[n];
    for(int i = 0; i < n; i++){
      cin >> v[i];
    }
    cout << solve(n, k, v) << "\n";
    delete[] v;
  }
  return 0;
}
