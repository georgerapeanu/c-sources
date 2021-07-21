#include <bits/stdc++.h>

using namespace std;

int t;
vector<int> vals;

int main(){

  scanf("%d",&t);

  while(t--){
    vals = vector<int>(4,0);
    for(auto &it:vals){
      scanf("%d",&it);
    }

    vector<int> ans = {max(vals[0],vals[1]),max(vals[2],vals[3])};
    sort(ans.begin(),ans.end(),greater<int>());
    sort(vals.begin(),vals.end(),greater<int>());
    vals.resize(2);
    printf(ans == vals ? "YES\n":"NO\n");
  }

  return 0;
}
