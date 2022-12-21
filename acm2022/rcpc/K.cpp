#include <bits/stdc++.h>

using namespace std;

int main(){

  int n, d;
  scanf("%d %d", &n, &d);

  vector<vector<int>> v(d);

  for(int i = 0;i < n;i++){
    int value;
    scanf("%d", &value);
    v[i % d].push_back(value);
  }
  
  for(int i = 0;i < d;i++){
    sort(v[i].begin(), v[i].end()); 
  }

  int last_value = 1e9 + 5;

  for(int i = n - 1;i >= 0;i--){
    int value = v[i % d].back();
    v[i % d].pop_back();
    if(last_value < value){
      cout << "NO\n";
      return 0;
    }
    last_value = value;
  }
  
  cout << "YES\n";

  return 0;
}
