#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);
 
  for(int test = 1;test <= t;test++){
    printf("Case #%d: ", test);

    int n;
    scanf("%d", &n);
    vector<int> v(n, 0);
    for(auto &it:v){
      scanf("%d", &it);
    }
    sort(v.begin(), v.end());

    int cnt = 1;

    for(auto it:v){
      cnt += (cnt <= it);
    }
    printf("%d\n", cnt - 1);
  }
  return 0;
}
