#include <cstdio>

using namespace std;

int N;
int V[1000005];
const int MOD = 998244353;

int main(){

    scanf("%d",&N);

    for(int i = 1;i <= N;i++){
        scanf("%d",&V[i]);
    }

    int ans = 0;
    int pw = 1;
    for(int i = N - 1;i;i--){
        ans = (ans + (1LL * (1LL * (N - i) * pw % MOD + 2 * pw) * V[i])) % MOD;
        pw *= 2;
        if(pw >= MOD){
            pw -= MOD;
        }
    }

    ans += V[N];
    if(ans >= MOD){
        ans -= MOD;
    }

    printf("%d",ans);

    return 0;
}
