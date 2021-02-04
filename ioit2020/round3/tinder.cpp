#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int XMAX = 1e5;

int n,x;
int dp[XMAX + 5];

int main(){
    
    scanf("%d %d",&n,&x);

    for(int i = 1;i <= n;i++){
        int p,q;
        scanf("%d %d",&p,&q);
        for(int j = x;j >= q;j--){
            dp[j] = max(dp[j],dp[j - q] + p);
        }
    }

    printf("%d\n",dp[x]);


    return 0;
}
