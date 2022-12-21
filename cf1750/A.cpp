#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);

    vector<int> v(n, 0);
    for(auto &it:v){
      scanf("%d", &it);
    }
    
    for(int i = 1;i < n;i++){
      if(v[i] < v[0]){
        printf("No\n");
        goto done;
      }
    }
    printf("Yes\n");
    done:;
  }

  return 0;
}
