#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  cin >> t;

  while(t--){
    int n;
    string s;
    cin >> n;
    cin >> s;

    int last = -1;
    int last_cnt = 0;

    long long ans = 0;
    int fr[] = {0, 0};

    for(auto &it:s){
      if(it != last){
        last = it;
        last_cnt = 0;
      }
      last_cnt++;
      ans = max(ans, 1LL * last_cnt * last_cnt);
      fr[it - '0']++;
    }

    ans = max(ans, 1LL * fr[0] * fr[1]);

    cout << ans << "\n";
  }

  return 0;
}
