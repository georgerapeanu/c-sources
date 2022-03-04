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
      int biggest[] = {-1, -1};


      bool ok = true;
      for(auto it:v){
        if(biggest[it & 1] > it){
          ok = false;
        }
        biggest[it & 1] = max(biggest[it & 1], it);
      }
      printf(ok ? "Yes\n":"No\n");
    }

    return 0;
}
