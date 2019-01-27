#include <cstdio>
#include <algorithm>

using namespace std;

struct data_t{
    long long a,b,k;
    bool operator < (const data_t &other)const{return b > other.b;}
};

int n;
long long ans;

data_t stuff[505];
long long dp[505];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%lld %lld %lld",&stuff[i].a,&stuff[i].b,&stuff[i].k);
    }

    sort(stuff + 1,stuff + 1 + n);

    for(int i = 1;i <= n;i++){
        for(int j = n - 1;j >= 0;j--){
            dp[j + 1] = max(dp[j + 1],dp[j] + stuff[i].a - j * stuff[i].b);
            dp[j] = max(dp[j],dp[j] + stuff[i].a - stuff[i].k * stuff[i].b);
        }
    }

    for(int i = 0;i <= n;i++){
        ans = max(ans,dp[i]);
    }

    printf("%lld",ans);

    return 0;
}
