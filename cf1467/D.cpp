#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e3;
const int KMAX = 5e3;
const int MOD = 1e9 + 7;

int n,k,q;
int dp[KMAX + 2][NMAX + 1];
int coef[NMAX + 5];
int a[NMAX + 5];

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}



int main(){

    scanf("%d %d %d",&n,&k,&q);

    k++;

    for(int i = 1;i <= n;i++){
        dp[1][i] = 1;
    }

    for(int h = 2;h <= k;h++){
        for(int i = 1;i <= n;i++){
            dp[h][i] = add((i > 1 ? dp[h - 1][i - 1] : 0),(i < n ? dp[h - 1][i + 1]:0));
        }
    }

    for(int h = 1;h <= k;h++){
        for(int i = 1;i <= n;i++){
            coef[i] = add(coef[i],mult(dp[h][i],dp[k - h + 1][i]));
        }
    }

    int sum = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        sum = add(sum,mult(a[i],coef[i]));
    }

    while(q--){
        int i,x;
        scanf("%d %d",&i,&x);
        sum = scad(sum,mult(a[i],coef[i]));
        a[i] = x;
        sum = add(sum,mult(a[i],coef[i]));
        printf("%d\n",sum);
    }

    return 0;
}
