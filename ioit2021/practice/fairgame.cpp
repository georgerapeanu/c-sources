#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e6;

int n,k,m,p,q;
long long dp[NMAX + 5];
deque<int> dq[2];

int main(){

    scanf("%d %d %d %d %d",&n,&k,&m,&p,&q);

    dp[0] = q - p;
    dq[0].push_back(0);

    for(int i = 1;i <= n;i++){
        for(int h = 0;h < 2;h++){
            while(dq[h].empty() == false && dq[h].front() < i - k){
                dq[h].pop_front();
            }
        }
        dp[i] = -1e18;
        for(int h = 0;h < 2;h++){
            if(dq[h].empty() == false){
                dp[i] = max(dp[i],((i & 1) == h ? 0:-m) - dp[dq[h].front()]);
            }
        }
        while(dq[i & 1].empty() == false && dp[dq[i & 1].back()] >= dp[i]){
            dq[i & 1].pop_back();
        }
        dq[i & 1].push_back(i);
    }

    printf("%lld\n",dp[n]);

    return 0;
}
