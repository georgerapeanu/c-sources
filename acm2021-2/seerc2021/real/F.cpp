#include <bits/stdc++.h>

using namespace std;

int main(){

  int n,x,r,p,k;
  string s;


  cin >> n >> x >> r >> p >> k;
  cin >> s;
  s = " " + s;

  long long ans = 1LL * x * n;

  vector<long long> cost;

  for(int i = 1;i <= n;i++){
    if(s[i] == '0'){
      cost.push_back(1LL * (n - i + 1) * p); 
    }else{
      ans -= 1LL * (n - i + 1) * r;
      cost.push_back(1LL * (n - i + 1) * (p + r)); 
    }
  }

  sort(cost.begin(),cost.end());
  reverse(cost.begin(),cost.end());

  for(auto it:cost){
    if(k == 0){
      break;
    }
    ans += it;
    k--;
  }

  cout << ans << "\n";

    return 0;
}
