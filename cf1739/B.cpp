#include <bits/stdc++.h>

using namespace std;

int main(){
    
    int t;
    
    scanf("%d", &t);

    while(t--){
      int n;
      scanf("%d", &n);

      int sum = 0;

      vector<int> v;
      int answer = 0;

      for(int i = 1;i <= n;i++){
        int value;
        scanf("%d", &value);

        if(sum >= value && i > 1 && value > 0){
          answer = -1;
        }

        sum += value;
        v.push_back(sum);
      }
      
      if(answer == -1){
        printf("%d\n", answer);
      }else{
        for(auto it:v){
          printf("%d ", it);
        }
        printf("\n");
      }
    }


    return 0;
}
