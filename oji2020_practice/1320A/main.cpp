#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int NMAX = 2e5;

int n;
int b[NMAX + 5];
map<int,long long> best;

int main(){

    scanf("%d",&n);

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        scanf("%lld",&b[i]);
        best[b[i] - i] += b[i];
        ans = max(ans,best[b[i] - i]);
    }

    printf("%lld\n",ans);

    return 0;
}
