#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);
    int matched_prefix = 0;
    vector<int> v(n, 0);

    for(auto &it:v){
      scanf("%d", &it);
    }

    vector<pair<int,int> > ops;

    vector<int> groups;

    while(v.empty() == false){
      int pos = -1;
      for(int i = 1;i < (int)v.size();i++){
        if(v[0] == v[i]){
          pos = i;
          break;
        }
      }
      if(pos == -1){
        break;
      }
      for(int i = 0;i < pos;i++){
        ops.push_back({matched_prefix + pos + i, v[i]});
      }
      groups.push_back(2 * pos);
      matched_prefix += 2 * pos;
      reverse(v.begin(), v.begin() + pos);

      for(int i = 0;i < pos + 1;i++){
        ops.push_back({matched_prefix + pos + 1 + i, v[i]});
      }
      groups.push_back(2 * (pos + 1));
      matched_prefix += 2 * (pos + 1);

      reverse(v.begin(), v.begin() + pos + 1);
      reverse(v.begin(), v.end());
      v.pop_back();
      v.pop_back();
      reverse(v.begin(), v.end());
      groups.push_back(2);
      matched_prefix += 2;
    }

    if(v.empty()){
      printf("%d\n", (int)ops.size());
      for(auto it:ops){
        printf("%d %d\n", it.first, it.second);
      }
      printf("%d\n", (int)groups.size());
      for(auto it:groups){
        printf("%d ", it);
      }
      printf("\n");
    }else{
      printf("-1\n");
    }
  }

  return 0;
}
