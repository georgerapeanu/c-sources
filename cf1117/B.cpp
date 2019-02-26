#include <cstdio>
#include <algorithm>

using namespace std;

int n,m,k;
int v[200005];

int main(){

    scanf("%d %d %d",&n,&m,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    int full_buck = m / (k + 1);
    int rem = m - full_buck * (k + 1);

    long long ans = 1LL * full_buck * (1LL * v[1] * k + v[2]) + 1LL * rem * v[1];

    printf("%lld",ans);

    return 0;
}
