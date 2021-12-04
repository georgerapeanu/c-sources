#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main(){

  cin >> n;
  cin >> s;

  vector<int> fr(3,0);

  for(auto it:s){
    fr[it - 'A']++;
  }

  set<int> active[2];

  vector<pair<int,int> > ans;

  for(int i = 0;i < 2 * n;i++){
    if(s[i] == 'A'){
      active[0].insert(i);
    }else if(s[i] == 'B'){
      if(fr[0] < n){
        fr[0]++;
        active[1].insert(i);
      }else{
        fr[1]++;
        if(active[0].empty()){
          cout << "NO\n";
          return 0;
        }
        ans.push_back({*active[0].begin(),i});
        active[0].erase(active[0].begin());
      }
    }else{
      if(active[1].empty() == false){
        ans.push_back({*active[1].begin(),i});
        active[1].erase(active[1].begin());
      }else if(active[0].empty() == false){
        ans.push_back({*active[0].begin(),i});
        active[0].erase(active[0].begin());
      }else{
          cout << "NO\n";
          return 0;
      }
    }
  }
  
  if(active[0].empty() == false || active[1].empty() == false){
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";

  for(auto it:ans){
    cout << it.first + 1 << " " << it.second + 1 << "\n"; 
  }


    return 0;
}
