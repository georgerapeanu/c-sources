#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int len = 0;
pair<int,int> v[100005];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int l;
        scanf("%d",&l);
        int mi = 1e6;
        int ma = -1e6;

        bool ok = false;

        for(int i = 1; i <= l; i++) {
            int val;
            scanf("%d",&val);

            if(mi < val) {
                ok = true;
            }

            mi = min(mi,val);
            ma = max(ma,val);
        }

        if(ok == false) {
            v[++len] = {ma,mi};
        }
    }

    sort(v + 1,v + 1 + len);

    long long ans = 1LL * n * n;

    for(int i = 1; i <= len; i++) {
        int l = 0,r = len + 1;

        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(v[mid].first <= v[i].second) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        ans -= l;
    }

    printf("%lld\n",ans);

    return 0;
}
