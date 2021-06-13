#include <bits/stdc++.h>

using namespace std;

int n,s;

const int NMAX = 256;
const int SHIFT = NMAX * (NMAX - 1) / 2 + 2;
const int SZ = NMAX * (NMAX - 1) + 5;
int dp[2][NMAX * (NMAX - 1) + 5];

const int MOD = 194767;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int main(){

    freopen("1-sir.in","r",stdin);
    freopen("1-sir.out","w",stdout);

    scanf("%d %d",&n,&s);

    dp[0][SHIFT] = 1;

    for(int i = 0,h = 0;i < n - 1;i++,h ^= 1){
        for(int j = SHIFT - i * (i + 1) / 2;j <= SHIFT + i * (i + 1) / 2 ;j++){
            dp[h ^ 1][j - (i + 1)] = add(dp[h ^ 1][j - (i + 1)],dp[h][j]);
            dp[h ^ 1][j + (i + 1)] = add(dp[h ^ 1][j + (i + 1)],dp[h][j]);
            dp[h][j] = 0;
        }
    }

    printf("%d\n",(s + SHIFT >= 0 && s + SHIFT < SZ ? dp[(n - 1) & 1][s + SHIFT]:0));

    return 0;
}
