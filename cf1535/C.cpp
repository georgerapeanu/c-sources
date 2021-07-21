#include <bits/stdc++.h>

using namespace std;

int t;
string s;
int fr[2][2];

int main(){

  cin >> t;
  
  while(t--){
    cin >> s;
    memset(fr,0,sizeof(fr));
    int l = 0;
    long long ans = 0;
    for(int r = 0;r < (int)s.size();r++){
      if(s[r] != '?'){
        fr[r & 1][s[r] - '0']++;
      }
      while((fr[0][0] > 0) + (fr[0][1] > 0) > 1 || (fr[1][0] > 0) + (fr[1][1] > 0) > 1 || (fr[0][0] > 0) + (fr[1][0] > 0) > 1 || (fr[0][1] > 0) + (fr[1][1] > 0) > 1){
        if(s[l] != '?'){
          fr[l & 1][s[l] - '0']--;
        }
        l++;
      }
      ans += (r - l + 1);
    }
    cout << ans << "\n";
  }

  return 0;
}
