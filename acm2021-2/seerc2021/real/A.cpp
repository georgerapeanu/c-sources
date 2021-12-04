#include <bits/stdc++.h>

using namespace std;

int n;
string s;
string t;

int main(){

  cin >> n;
  cin >> s;
  cin >> t;

  int last_pos_smaller = n;
  int last_pos_bigger = n;

  long long ans = 0;

  for(int i = n - 1;i >= 0;i--){
    if(s[i] < t[i]){
      last_pos_smaller = i;
    }
    if(s[i] > t[i]){
      last_pos_bigger = i;
    }
    if(last_pos_smaller < last_pos_bigger){
      ans += n - last_pos_smaller;
    }
  }

  cout << ans;

  return 0;
}
