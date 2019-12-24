#include <bits/stdc++.h>

using namespace std;

int t;
int n,p,k;
int a[200005];
int sum[200005];
int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d %d",&n,&p,&k);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
        }

        sort(a + 1,a + 1 + n);

        for(int i = 1; i <= n; i++) {
            sum[i] = a[i] + (i > k ? sum[i - k]:0);
        }

        int ans = 0;

        for(int i = 0; i < k; i++) {
            p -= a[i];
            if(p < 0) {
                break;
            }
            int l = 0,r = n;

            while(r - l > 1) {
                int mid = (l + r) / 2;
                if(i + 1LL * mid * k > n || sum[i + 1LL * mid * k] - sum[i] > p) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            ans = max(ans,i + k * l);
        }

        printf("%d\n",ans);

    }

    return 0;
}
