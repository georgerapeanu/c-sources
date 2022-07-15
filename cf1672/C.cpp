#include <bits/stdc++.h>

using namespace std;

int main(){
  

  int t;
  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);
    
    vector<int> v(n + 1, 0);

    int fst = -1;
    int lst = -1;

    for(int i = 1;i <= n;i++){
      scanf("%d", &v[i]);
      if(i > 1 && v[i - 1] == v[i]){
        if(fst == -1){
          fst = i - 1;
        }
        lst = i - 1;
      }
    }

    if(fst == lst){
      printf("0\n");
    }else{
      printf("%d\n", max(lst - fst - 1, 1));
    }
  }

  return 0;
}
