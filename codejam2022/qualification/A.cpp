#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;

  cin >> t;

  for(int test = 1;test <= t;test++){
    cout << "Case #" << test << ": " << "\n";
    int n, m;
    cin >> n >> m;

    for(int i = 1;i <= 2 * n + 1;i++){
      for(int j = 1;j <= 2 * m + 1;j++){
        if(i <= 2 && j <= 2){
          cout << ".";
        }else if(i % 2 == 0 && j % 2 == 0){
          cout << ".";
        }else if(i % 2 == 0 && j % 2 == 1){
          cout << "|";
        }else if(i % 2 == 1 && j % 2 == 0){
          cout << "-";
        }else{
          cout << "+";
        }
      }
      cout << "\n";
    }
  }

  return 0;
}
