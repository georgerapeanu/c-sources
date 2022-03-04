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


    int lft = 0, rgt = 0;
    for(int i = 0;i < n;i++){
      if(v[i] != i + 1){
        lft = i;
        for(int j = i;j < n;j++){
          if(v[j] == i + 1){
            rgt = j;
            break;
          }
        }
        break;
      }
    }
    reverse(v.begin() + lft, v.begin() + rgt + 1);

    for(auto it:v){
      printf("%d " ,it);
    }
    printf("\n");

  }


  return 0;
}
