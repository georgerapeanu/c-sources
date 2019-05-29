#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int> > events;

int n;

int main() {
    scanf("%d",&n);

    long long coord = -1e9 - 1;
    long long cost = 0;
    int active_lefts = 0;
    int active_rights = 0;

    for(int i = 1; i <= n; i++) {
        int l,r;
        scanf("%d %d",&l,&r);
        events.push_back({l,0});
        events.push_back({r,1});
        cost += (l - coord);
        active_lefts++;
    }

    sort(events.begin(),events.end());

    long long ans = 1e18;

    for(auto it:events) {
        ///move line
        cost += 1LL * (active_rights - active_lefts) * (it.first - coord);

        coord = it.first;

        ans = min(ans,cost);

        if(it.second == 0) {
            active_lefts--;
        }
        else {
            active_rights++;
        }
    }

    printf("%lld",ans);

    return 0;
}
