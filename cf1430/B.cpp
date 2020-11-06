#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;

    scanf("%d",&t);

    while(t--){
        int n,k;
        scanf("%d %d",&n,&k);
        vector<int> v(n,0);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i - 1]);
        }

        sort(v.begin(),v.end());
        reverse(v.begin(),v.end());

        long long ans = 0;

        for(int i = 0;i <= k;i++){
            ans += v[i];
        }

        printf("%lld\n",ans);
    }

    return 0;
}
