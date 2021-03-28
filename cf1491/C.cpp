#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e3;

int t;
int n;
int s[NMAX + 5];
long long cnt[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&s[i]);
            cnt[i] = 0;
        }

        long long ans = 0;

        for(int i = 1;i <= n;i++){
            cnt[i] += cnt[i - 1];
            cnt[i + 2]++;
            cnt[min(i + s[i] + 1,n + 1)]--;
            if(cnt[i] > s[i] - 1){
                cnt[i + 1] += cnt[i] - s[i] + 1;
                cnt[i + 2] -= cnt[i] - s[i] + 1;
            }
            s[i] = max(1LL,s[i] - cnt[i]);
            ans += max(0,s[i] - 1);
            s[i] = 1;
        }

        printf("%lld\n",ans);
    }

    return 0;
}
