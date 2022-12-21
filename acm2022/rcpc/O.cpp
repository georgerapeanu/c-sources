#include <bits/stdc++.h>

using namespace std;

int main(){

  long double e = 0;

  int n, m;
  cin >> n >> m;

  for(int i = 1;i <= m;i++){
    e = (e / n) * e + ((n - e) / n) * (e + 1);
  }

  cout << fixed << setprecision(10) << e;

  return 0;
}
