#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  map<string, vector<int> > data;
  map<string, int> fitToInt;
  fitToInt["left"] = 0;
  fitToInt["right"] = 1;
  fitToInt["any"] = 2;

  cin >> n;

  int totalCount = 0;
  for(int i = 1;i <= n;i++){
    string type;
    string fit;
    int count;
    cin >> type >> fit >> count;
    totalCount += count;
    if(data.count(type) == 0){
      data[type] = vector<int>(3, 0);
    }
    data[type][fitToInt[fit]] += count;
  }

  int ans = 1;

  for(auto it:data){
    ans += max(max(it.second[0], it.second[1]), min(it.second[2], 1));
  }

  if(ans > totalCount){
    cout << "impossible\n";
  }else {
    cout << ans << "\n";
  }
  return 0;
}
