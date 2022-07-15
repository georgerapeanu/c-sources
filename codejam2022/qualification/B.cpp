#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;
  cin >> t;

  for(int test = 1;test <= t;test++){
    cout << "Case #" << test << ": ";
    int levels[4];
    for(int i = 0;i < 4;i++){
      levels[i] = 1e9;
    }
    for(int i = 0;i < 3;i++){
      for(int j = 0;j < 4;j++){
        int level;
        cin >> level;
        levels[j] = min(levels[j], level);
      }
    }
    int required_level = 1e6;
    for(int i = 0;i < 4;i++){
      if(required_level > levels[i]){
        required_level -= levels[i];
      }else{
        levels[i] = required_level;
        required_level = 0;
      }
    }
    if(required_level > 0){
      cout << "IMPOSSIBLE";
    }else{
      for(int i = 0;i < 4;i++){
        cout << levels[i] << " ";
      }
    }

    cout << "\n";
  }

  return 0;
}
