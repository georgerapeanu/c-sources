#include <bits/stdc++.h>

using namespace std;

int main(){
    
    int t;

    scanf("%d",&t);

    while(t--){
      int n,m,a,b;
      scanf("%d %d %d %d",&n,&m,&a,&b);

      if(a > b){
        a = n - a + 1;
        b = n - b + 1;
      }
      
      vector<int> petarde(m);
      for(auto &it:petarde){
        scanf("%d",&it);
      }

      sort(petarde.begin(),petarde.end());

      int __max = -1e9;
      int ans = 0;
      
      for(int i = 0;i < (int)petarde.size() && i < b - a - 1;i++){
        __max = max(__max,petarde[i] - i);
        if(__max <= b - (i + 1) - 1){
          ans = i + 1;
        }
      }
      printf("%d\n",ans);
    }

    return 0;
}
