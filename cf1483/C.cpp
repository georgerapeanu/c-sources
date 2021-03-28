#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n;
int len;
int v[NMAX + 5];
int b[NMAX + 5];
long long dp[NMAX + 5];
pair<int,long long> st[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
    }

    v[0] = 1e9;

    for(int i = 1;i <= n;i++){
        pair<int,long long> current = {i,-1e9};
        while(len > 0 && v[st[len].first] > v[i]){
            current.second = max(current.second,st[len].second);
            len--;
        }
        current.second = max(current.second,dp[st[len].first]);
        dp[i] = max(dp[st[len].first] + b[i] * (len == 0),current.second + b[i]);
        current.second = max(dp[i],current.second);
        st[++len] = current;
    }

    printf("%lld\n",dp[n]);

    return 0;
}
