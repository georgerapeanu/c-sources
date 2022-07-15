#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;
  cin >> t;

  while(t--){
    string s;
    cin >> s;

    int dif = 0;
    
    bool ok = (s.back() == 'B');
    for(auto it:s){
      dif += (it == 'A' ? 1:-1);
      if(dif < 0){
        ok = false;
        break;
      }
    }
    printf(ok ? "YES\n":"NO\n");
  }
  return 0;
}
