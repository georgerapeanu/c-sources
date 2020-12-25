#include <bits/stdc++.h>

using namespace std;

int t;
int n;
vector<int> v;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        v = vector<int>(n,0);

        for(int i = 0;i < n;i++){
            scanf("%d",&v[i]);
        }

        sort(v.begin(),v.end());

        long long ans = 0;
        long long sum = 0;
        int ma = 0;
        for(auto it:v){
            sum += it;
            ma = max(ma,it);
        }
        long long target_sum = max(1LL * ma * (n - 1),sum);
        target_sum += ((n - 1) - (target_sum % (n - 1))) % (n - 1);
        ans = target_sum - sum;

        printf("%lld\n",ans);
    }

    return 0;
}
