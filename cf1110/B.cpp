#include <cstdio>
#include <algorithm>

using namespace std;

int n,m,k;
int v[int(1e5) + 10];
int a[int(1e5) + 10];
int main() {

    scanf("%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        if(i > 1) {
            a[i - 1] = v[i] - v[i - 1];
        }
    }

    sort(a + 1,a + n);
    reverse(a + 1,a + n);
    int ans = v[n] - v[1];

    for(int i = 1; i < k; i++) {
        ans -= a[i];
    }

    printf("%d",ans + k);

    return 0;
}
