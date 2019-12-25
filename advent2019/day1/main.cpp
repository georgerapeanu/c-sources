#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int val;
    long long ans = 0;
    while(scanf("%d",&val) == 1) {
        while(val > 0) {
            ans += max(0,(val / 3) - 2);
            val = val / 3 - 2;
        }

    }

    printf("%lld\n",ans);

    return 0;
}
