#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long x[500005];

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

    int t;
    scanf("%d",&t);

    while(t--){
        vector<int> fr(60,0);
        int n;
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%lld",&x[i]);

            for(int h = 0;h < (int)fr.size();h++){
                fr[h] += ((x[i] >> h) & 1);
            }
        }

        int ans = 0;

        for(int j = 1;j <= n;j++){
            int sum_or = 0;
            int sum_and = 0;
            int pw2 = 1;

            for(int h = 0;h < (int)fr.size();h++){
                if((x[j] >> h) & 1){
                    sum_and = add(sum_and,mult(pw2,fr[h]));
                    sum_or = add(sum_or,mult(pw2,n));
                }else{
                    sum_and = sum_and;
                    sum_or = add(sum_or,mult(pw2,fr[h]));
                }
                pw2 = add(pw2,pw2);
            }
            ans = add(ans,mult(sum_or,sum_and));
        }

        printf("%d\n",ans);
    }

    return 0;
}
