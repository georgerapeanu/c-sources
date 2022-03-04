#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;
  cin >> t;
  string s;

  while(t--){
    cin >> s;
    int fr[] = {0, 0};

    for(auto it:s){
      fr[it - '0'] ++;
    }

    cout << min(fr[0], fr[1]) - (fr[0] == fr[1]) << "\n";
  }

    return 0;
}
