#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int n;
int dp[2][5005];
int tmp[2][5005];

int a[5005];
int _less[5005];
int _more[5005];

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }

    sort(a + 1,a + 1 + n);

    for(int i = 1;i <= n;i++){
        _less[i] = _less[i - 1];
        while(a[_less[i] + 1] * 2 <= a[i]){
            _less[i]++;
        }
    }

    _more[n + 1] = n + 1;

    for(int i = n;i;i--){
        _more[i] = _more[i + 1];
        while(a[_more[i] - 1] >= 2 * a[i]){
            _more[i]--;
        }
    }

    dp[0][0] = 1;
    _less[0] = -1;
    _more[0] = 1;

    for(int i = 0,l = 0;i <= n;i++,l ^= 1){
        for(int j = 0;j <= n;j++){
            if(j > 0){
                tmp[l][j] = add(tmp[l][j],tmp[l][j - 1]);
            }
            dp[l][j] = add(dp[l][j],tmp[l][j]);
        }
        for(int j = 0;j <= n;j++){
            dp[l ^ 1][j] = 0;
            tmp[l ^ 1][j] = 0;
        }
        for(int j = 0;j <= n;j++){
            if(_less[j] - (i - 1) > 0){
                dp[l ^ 1][j] = add(dp[l ^ 1][j],mult(dp[l][j],_less[j] - (i - 1)));
            }
            tmp[l ^ 1][_more[j]] = add(tmp[l ^ 1][_more[j]],dp[l][j]);
        }
    }

    printf("%d\n",dp[n & 1][n]);

    return 0;
}
