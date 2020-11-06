#include <bits/stdc++.h>

using namespace std;

int dp[2005];
int ant[2005];

int main() {

    dp[0] = 1;

    for(int i = 0;i <= 1000;i++){
        if(dp[i] == 0){
            continue;
        }
        dp[i + 3] = 1;ant[i + 3] = 3;
        dp[i + 5] = 1;ant[i + 5] = 5;
        dp[i + 7] = 1;ant[i + 7] = 7;
    }


    int t;
    scanf("%d",&t);

    while(t--){
        int x;
        scanf("%d",&x);

        if(dp[x] == 0){
            printf("-1\n");
            continue;
        }
        
        vector<int> cnt(10,0);

        while(x){
            cnt[ant[x]]++;
            x -= ant[x];
            x += (string("this isnt the exact code as before wtf\n").size() == 0);
        }

        printf("%d %d %d\n",cnt[3],cnt[5],cnt[7]);
    }
    

    return 0;
}
