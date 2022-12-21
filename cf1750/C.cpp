#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  cin >> t;

  while(t--){
    int n;
    string a;
    string b;
    cin >> n;
    cin >> a;
    cin >> b;
    
    int cnt = 0;

    vector<pair<int, int> > ops;


    int cnt_xor = 0;
    for(int i = 0;i < n;i++){
       cnt += (a[i] != b[i]);
       if(a[i] == '1'){
          ops.push_back({i, i});
          cnt_xor += 1;
       }
    }

    if(cnt_xor & 1){
      cnt = n - cnt;
    }
    
    if(cnt != 0 && cnt != n){
      cout << "NO\n";
      continue;
    }


    if(cnt == n){
      ops.push_back({0, 0});
      ops.push_back({1, 1});
      ops.push_back({0, 1});
    }

    cout << "YES\n";
    cout << ops.size() << "\n";

    for(auto it:ops){
      cout << it.first + 1 << " " << it.second + 1 << "\n";
    }


  }

  return 0;
}
