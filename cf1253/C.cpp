#include <bits/stdc++.h>

using namespace std;

int n,m;
int v[200005];
long long sum[200005];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        sum[i] = v[i];
        if(i >= m) {
            sum[i] += sum[i - m];
        }
        ans += sum[i];
        printf("%lld ",ans);
    }

    return 0;
}
