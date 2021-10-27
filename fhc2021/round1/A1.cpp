#include <bits/stdc++.h>

using namespace std;

int t;
int n;
string s;

int main(){
  
  cin >> t;

  for(int h = 1;h <= t;h++){
    cin >> n;
    cin >> s;

    int ans = 0;
    char lst = -1;

    for(auto it:s){
      if(it == 'F'){
        continue;
      }
      ans += (lst != -1 && lst != it);
      lst = it;
    }

    printf("Case #%d: %d\n",h,ans);
  }

  return 0;
}
