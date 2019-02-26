#include <cstdio>
#include <map>

using namespace std;

const int NMAX = 3e5;

int n;
int v[NMAX + 5];

map<int,int> fr[2];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
        v[i] ^= v[i - 1];
        fr[i & 1][v[i]]++;
    }

    fr[0][0]++;

    long long ans = 0;

    for(auto it:fr[0]){
        ans += 1LL * it.second * (it.second - 1) / 2;
    }


    for(auto it:fr[1]){
        ans += 1LL * it.second * (it.second - 1) / 2;
    }

    printf("%lld",ans);

    return 0;
}
