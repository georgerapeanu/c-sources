#include <bits/stdc++.h>

using namespace std;

int n;
int p,q;

int main(){

  int ans = 0;

  cin >> n;

  while(n--){
    cin >> p >> q;
    ans += (q - p >= 2);
  }

  cout << ans << "\n";

  return 0;
}
