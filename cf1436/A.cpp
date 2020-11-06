#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
  
    scanf("%d",&t);

    while(t--){
        int n;
        int sum = 0;
        scanf("%d %d",&n,&sum);

        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            sum -= val;
        }

        printf(sum == 0 ? "YES\n":"NO\n");
    }

    return 0;
}
