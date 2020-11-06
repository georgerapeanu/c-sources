#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

int n,k;
vector<int> v[3003];
int64 sum[3003];

int64  dp[3005][3005];
int length_dp;

int64 ans = 0;

void solve(int st,int dr) {
    if(st == dr) {
        ans = max(ans,dp[length_dp][k]);

        int64 local_sum = 0;

        for(int i = 0;i < (int)v[st].size() && i < k;i++){
            local_sum += v[st][i];
            ans = max(ans,local_sum + dp[length_dp][k - i - 1]);
        }

        return;
    }

    int mid = (st + dr) / 2;

    for(int i = dr;i > mid;i--) {
        length_dp++;
        for(int j = k;j >= (int)v[i].size();j--) {
            dp[length_dp][j] = max(dp[length_dp - 1][j],dp[length_dp - 1][j - (int)v[i].size()] + sum[i]);
        }
        for(int j = (int)v[i].size() - 1;j >= 0;j--){
            dp[length_dp][j] = dp[length_dp - 1][j];
        }
    }

    solve(st,mid);

    length_dp -= (dr - mid);

    for(int i = st;i <= mid;i++) {
        length_dp++;
        for(int j = k;j >= (int)v[i].size();j--) {
            dp[length_dp][j] = max(dp[length_dp - 1][j],dp[length_dp - 1][j - (int)v[i].size()] + sum[i]);
        }
        for(int j = (int)v[i].size() - 1;j >= 0;j--){
            dp[length_dp][j] = dp[length_dp - 1][j];
        }
    }

    solve(mid + 1,dr);

    length_dp -= (mid - st + 1);
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

int main() {

    n = i32();
    k = i32();

    for(int i = 1;i <= n;i++) {
        int length;
        
        length = i32();

        v[i] = vector<int>(length);

        for(auto &itr:v[i]) {
            itr = i32();
            sum[i] += itr;
        }
    }

    length_dp = 1;

    solve(1,n);

    printf("%lld\n",ans);

    return 0;
}
