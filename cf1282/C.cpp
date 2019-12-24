#include <bits/stdc++.h>

using namespace std;

int t;

int main() {

    scanf("%d",&t);

    while(t--) {
        int n,tl,a,b;

        scanf("%d %d %d %d",&n,&tl,&a,&b);

        vector<pair<int,int> > v = {make_pair(0,-1)};

        int ans = 0,cnt0 = 0,cnt1 = 0;
        for(int i = 0; i < n; i++) {
            int mode;
            scanf("%d",&mode);
            v.push_back({0,mode});
            if(mode == 0) {
                cnt0++;
            }
            else {
                cnt1++;
            }
        }

        for(int i = 0; i < n; i++) {
            int ti;
            scanf("%d",&ti);
            v[i + 1].first = ti;
        }

        sort(v.begin(),v.end());

        long long sum = 0;

        v.push_back({tl + 1,0});

        for(int i = 0; i <= n; i++) {
            ///including i
            if(v[i].second == 0) {
                cnt0--;
            }
            else if(v[i].second == 1) {
                cnt1--;
            }
            if(v[i].second != -1) {
                sum += (v[i].second == 0 ? a:b);
            }
            if(sum < v[i + 1].first) {
                int tmp_ans = i;
                int tmp_0 = min((v[i + 1].first - sum - 1) / a,1LL * cnt0);
                tmp_ans += tmp_0;
                int tmp_1 = min((v[i + 1].first - sum - 1 - a * tmp_0) / b,1LL * cnt1);
                tmp_ans += tmp_1;
                ans = max(ans,tmp_ans);
            }

        }

        printf("%d\n",ans);
    }

    return 0;
}
