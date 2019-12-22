#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 50000;

int n,v;
int cost[NMAX + 5];
int voucher[NMAX + 5];

int main() {

    scanf("%d %d",&n,&v);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&cost[i]);
    }

    for(int i = 1; i <= v; i++) {
        scanf("%d",&voucher[i]);
    }

    sort(cost + 1,cost + 1 + n);
    sort(voucher + 1,voucher + 1 + v);

    int last = n;
    int ans = 0;

    for(int i = v; i; i--) {
        while(last > 0 && cost[last] > voucher[i]) {
            last--;
        }

        ans += (last > 0);
        last--;
    }

    printf("%d\n",ans);

    return 0;
}
