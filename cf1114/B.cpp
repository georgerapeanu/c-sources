#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;

int n,m,k;
pair<int,int> v[NMAX + 5];
bool take[NMAX + 5];


int main() {

    scanf("%d %d %d",&n,&m,&k);

    long long sum = 0;

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i].first);
        v[i].second = i;
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    for(int i = 1; i <= m * k; i++) {
        take[v[i].second] = true;
        sum += v[i].first;
    }

    printf("%lld\n",sum);

    int cnt = 0;
    int num = 1;

    for(int i = 1; i <= n; i++) {
        cnt += take[i];
        if(cnt >= m && num < k) {
            printf("%d ",i);
            num++;
            cnt = 0;
        }
    }

    return 0;
}
