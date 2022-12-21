#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int n, i, k;

  cin >> n >> i >> k;

  long double e = i;

  for(int i = 1;i <= k;i++){
    long double expected_if_taken = 1.0 / (n - e) * (1LL * n * n - e * e) / 4;
    e = ((e - 1) / n) * e + (1 - ((e - 1) / n) ) * expected_if_taken;
  }

  cout << fixed << setprecision(8) << e << "\n";

  return 0;
}
