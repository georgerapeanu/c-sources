#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
long long l[NMAX + 5][2];
long long r[NMAX + 5][2];

int a[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        scanf("%d",&a[i]);
    }

    l[1][0] = l[1][1] = 0;

    for(int i = 2; i <= n; i++) {
        l[i][0] = (l[i - 1][0] + (a[i - 1] - (a[i - 1] & 1))) * (a[i - 1] > 1);
        l[i][1] = max(l[i - 1][0],l[i - 1][1]) + (a[i - 1] - 1 + (a[i - 1] & 1));
    }

    r[n][0] = r[n][1] = 0;

    for(int i = n - 1; i; i--) {
        r[i][0] = (r[i + 1][0] + (a[i] - (a[i] & 1))) * (a[i] > 1);
        r[i][1] = max(r[i + 1][0],r[i + 1][1]) + (a[i] - 1 + (a[i] & 1));
    }

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        ans = max(ans,max(l[i][0] + r[i][0],max(l[i][0] + r[i][1],l[i][1] + r[i][0])));
    }

    printf("%lld\n",ans);

    return 0;
}
