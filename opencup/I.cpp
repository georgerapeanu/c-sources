#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

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

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(b,p);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int n,m;

int cst,inv_cst;
int segm[1005];
int dp[1005][1005];
vector<int> not0[1005];
int sum_column[1005];

int main(){

    int inv6 = lgpow(6,MOD - 2);

    while(scanf("%d %d",&n,&m) != EOF){

        for(int i = 0;i <= n;i++){
            segm[i] = 0;
            not0[i].clear();
            sum_column[i] = 0;
            for(int j = 0;j <= n;j++){
                dp[i][j] = 0;
            }
        }

        for(int i = 1;i <= m;i++){
            int l,r;
            scanf("%d %d",&l,&r);
            if(segm[r] == 0){
                segm[r] = l;
            }
            else{
                segm[r] = min(segm[r],l);
            }
        }   
        
        dp[0][0] = 1;
        not0[0].push_back(0);
        sum_column[0] = 1;
        cst = inv_cst = 1;

        for(int i = 0;i <= n;i++){
            for(int j = 0;j < segm[i];j++){
                for(auto k:not0[j]){
                    sum_column[k] = scad(sum_column[k],dp[j][k]);
                    dp[j][k] = 0;
                }
                not0[j].clear();
            }

            if(i < n){
                vector<int> tmp(n + 1,0);
                int total_sum = 0;
                for(int k = 0;k <= i;k++){
                    tmp[k] = mult(cst,sum_column[k]);
                    total_sum = add(total_sum,mult(cst,sum_column[k]));
                }

                cst = mult(cst,6);
                inv_cst = mult(inv_cst,inv6);

                for(int k = 0;k <= i;k++){
                    dp[k][i + 1] = add(dp[k][i + 1],mult(inv_cst,mult(2,tmp[k])));
                    sum_column[i + 1] = add(sum_column[i + 1],mult(inv_cst,mult(2,tmp[k])));
                    not0[k].push_back(i + 1);
                }
                dp[i + 1][i + 1] = add(dp[i + 1][i + 1],mult(inv_cst,mult(2,total_sum)));
                sum_column[i + 1] = add(sum_column[i + 1],mult(inv_cst,mult(2,total_sum)));
                not0[i + 1].push_back(i + 1);
            }
        }
        int ans = 0;

        for(int j = 0;j <= n;j++){
            for(int k = 0; k <= n;k++){
                ans = add(ans,mult(cst,dp[j][k]));
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
