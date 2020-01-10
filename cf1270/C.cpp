#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;
    scanf("%d",&t);


    while(t--) {
        int n;
        long long sum = 0;
        long long xo = 0;

        scanf("%d",&n);
        for(int i = 1; i <= n; i++) {
            long long val;
            scanf("%lld",&val);
            sum += val;
            xo ^= (2 * val);
        }

        vector<long long> ans = {};

        if(xo % 2 != sum % 2) {
            ans.push_back(1);
            sum++;
            xo ^= 2;
        }

        if(xo < sum) {
            xo ^= (1LL << 50);
            sum += (1LL << 49);
            ans.push_back(((xo - sum) / 2) ^ (1LL << 49));
            ans.push_back((xo - sum) / 2);
        }
        else {
            ans.push_back((xo - sum) / 2);
            ans.push_back((xo - sum) / 2);
        }

        printf("%d\n",(int)ans.size());
        for(auto it:ans) {
            printf("%lld ",it);
        }
        printf("\n");
    }

    return 0;
}
