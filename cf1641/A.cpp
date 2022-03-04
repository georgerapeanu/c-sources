#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);

  while(t--){
    int n, x;
    scanf("%d %d", &n, &x);

    vector<int> a(n, 0);

    for(auto &it:a){
      scanf("%d", &it);
    }
    sort(a.begin(), a.end());

    multiset<int> active;

    for(auto it:a){
      if(it % x == 0 && active.count(it / x)){
        active.erase(active.find(it / x));
      }else{
        active.insert(it);
      }
    }

    printf("%d\n", (int)active.size());
  }

  return 0;
}
