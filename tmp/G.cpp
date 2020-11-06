#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int k;
long long dp[NMAX + 5];
int f[10];

int main(){

    for(int i = 1;i <= NMAX;i++){
        dp[i] = -1e18;
    }

    scanf("%d",&k);

    k = 3 * (k - 1);

    int weight = 3;

    for(int i = 0;i < 6;i++){
        int val;
        scanf("%d",&val);
        f[i] = val;
        for(int i = 0;i < weight;i++){
            deque<pair<long long,int> > dq;
            long long OFFSET = 0;
            for(int j = i;j <= NMAX;j += weight){
                while((int)dq.size() > 0 && j - dq.front().second > 1LL * k * weight){
                    dq.pop_front();
                }
                long long real_val = dp[j] - OFFSET;
                if(dq.empty() == false){
                    dp[j] = max(dp[j],dq.front().first + OFFSET);
                }
                while((int)dq.size() > 0 && dq.back().first < real_val){
                    dq.pop_back();
                }
                dq.push_back({real_val,j});
                OFFSET += val;
            }
        }
        weight *= 10;
    }

    weight = 1;

    for(int d = 0;d < 6;d++){
        for(int i = NMAX;i >= 0;i--){
            for(int k = 0;k < 10;k++){
                if(i + k * weight <= NMAX){
                    dp[i + k * weight] = max(dp[i + k * weight],dp[i] + 1LL * f[d] * (k / 3) * (k % 3 == 0));
                }
            }
        }
        weight *= 10;
    }
    
    int q;

    scanf("%d",&q);

    while(q--){
        int n;
        scanf("%d",&n);
        printf("%lld\n",dp[n]);
    }

    return 0;
}

