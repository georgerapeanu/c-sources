#include <bits/stdc++.h>

using namespace std;

int n;
int p;
string s;

int main(){

  cin >> n;
  
  int ans = 0;
  int best = 1e9;


  for(int i = 1;i <= n;i++){
    cin >> p >> s;

    int fr2 = 0;
    int fr1 = 0;
    int fr0 = 0;

    for(auto it:s){
      fr2 += (it == '2');
      fr1 += (it == '1');
      fr0 += (it == '0');
    }

    if(fr2 >= 2 && fr1 >= 1 && fr0 >= 1){
      if(p < best){
        best = p;
        ans = i;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}
