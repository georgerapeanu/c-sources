#include <bits/stdc++.h>

using namespace std;

const int LGMAX = 20;
const int VMAX = (1 << 20);
const int MOD = 1e9 + 7;

int c[VMAX + 5];
long long pref_sum[VMAX + 5];
int full1[LGMAX + 5];
long long s[LGMAX + 5];
int cnt[LGMAX + 1][2];
long long cst[LGMAX + 1][2];

string l,r;
int dp[LGMAX + 5];

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

    for(int i = 1;i <= VMAX;i++){
        if(i % 2 == 0){
            c[i] = 1 + c[i / 2];
        }else if(i == 3){
            c[i] = 3;
        }else if((i % 2 == 1) && (((i - 1) / 2) % 2 == 1)){
            c[i] = 2 + c[(i + 1) / 2];
        }else{
            c[i] = 1 + c[i - 1];
        }
    }

    for(int i = 1;i <= VMAX;i++){
        pref_sum[i] = c[i] + pref_sum[i - 1];
    }


    cnt[0][0] = 1;cst[0][0] = 0;
    cnt[1][0] = 2;cst[1][0] = 3;
    cnt[1][1] = 0;cst[1][1] = 0;
    cnt[2][0] = 3;cst[2][0] = 2 + 3 + 3;
    cnt[2][1] = 1;cst[2][1] = 3;

    for(int i = 3;i <= LGMAX;i++){
        cnt[i][0] = cnt[i - 1][0] + cnt[i - 1][1] + cnt[i - 2][0];
        cst[i][0] = cst[i - 1][0] + cst[i - 1][1] + cnt[i - 1][0] + 2 * cnt[i - 1][1] + cst[i - 2][0] + 3 * cnt[i - 2][0];
        cnt[i][1] = 1;
        cst[i][1] = i + 1;
        for(int l = 1;l < i;l++){
            cnt[i][1] += cnt[i - l - 1][1];
            cst[i][1] += cst[i - l - 1][1] + (l + 2) * cnt[i - l - 1][1];
            if(l > 1){
                cnt[i][1] += cnt[i - l - 1][0];
                cst[i][1] += cst[i - l - 1][0] + (l + 2) * cnt[i - l - 1][0];
            }
        }
    }

    s[0] = 0;
    s[1] = 1;
    s[2] = 1 + 2 + 3;


    full1[1] = 1;
    full1[2] = 3;

    for(int i = 3;i <= LGMAX;i++){
        full1[i] = i + 2;
    }
   
    for(int i = 3;i <= LGMAX;i++){
        s[i] = s[i - 1] + full1[i];
        for(int l = 1;l < i;l++){
            s[i] += (full1[l] + 1) * cnt[i - l - 1][0] + cst[i - l - 1][0];
            s[i] += (full1[l + 1]) * cnt[i - l - 1][1] + cst[i - l - 1][1];
        }
    }

    for(int i = 1;i <= LGMAX;i++){
//        printf("%lld %lld\n",s[i],pref_sum[(1 << i) - 1]);
        printf("%d %d %d %d\n",cnt[i][0],cnt[i][1],cst[i][0],cst[i][1]);
    }


    return 0;
}
