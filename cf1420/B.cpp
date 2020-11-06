#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int val;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        vector<int> fr(31,0);

        for(int i = 1;i <= n;i++){
            scanf("%d",&val);
            int len = -1;

            while(val){
                len++;
                val >>= 1;
            }
            fr[len + 1]++;
        }

        long long ans = 0;

        for(auto &it:fr){
            ans = ans + 1LL * it * (it - 1) / 2;
        }
        
        printf("%lld\n",ans);
    }

    return 0;
}
