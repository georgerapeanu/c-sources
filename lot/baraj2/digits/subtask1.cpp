#include <bits/stdc++.h>

using namespace std;

const int NMAX = 18;
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

int n,m,b;
int s[NMAX + 5];
int dp[NMAX + 5][2];
int sum[NMAX + 5];
int diff[NMAX + 5];


bool ok(int i,int fst,int snd,int s,int t){
    if(fst < 0 || fst >= b || snd < 0 || snd >= b){
        return false;
    }
    if(i == n && (fst == 0 || snd == 0)){
        return false;
    }

    if(sum[i] != 3 * (b + 1) && fst + snd != sum[i]){
        return false;
    }

    if(diff[i] != 3 * (b + 1) && fst - snd != diff[i]){
        return false;
    }

    if((fst + snd + t) % b == s){
        return true;
    }
    return false;
}

int main(){

    scanf("%d %d %d",&n,&m,&b);

    for(int i = 1;i <= n;i++){
        scanf("%d",&s[i]);
        sum[i] = 3 * (b + 1);
        diff[i] = 3 * (b + 1);
    }
    reverse(s + 1,s + 1 + n);
    
    for(int i = 1;i <= m;i++){
        int _i,_j,_k;
        char c;
        scanf("%d %c %d %d",&_i,&c,&_j,&_k);
        _i = n - _i + 1;
        _j = n - _j + 1;
        if(c == '+'){
            if(sum[_i] == 3 * (b + 1)){
                sum[_i] = _k;
            }else if(sum[_i] != _k){
                printf("0\n");
                return 0;
            }
        }else{
            if(diff[_i] == 3 * (b + 1)){
                diff[_i] = _k;
            }else if(diff[_i] != _k){
                printf("0\n");
                return 0;
            }
        }
    }

    dp[0][0] = 1;

    for(int i = 1;i <= n;i++){
        if(sum[i] == 3 * (b + 1) && diff[i] == 3 * (b + 1)){
            dp[i][0] = add(mult(dp[i - 1][0],max(0,s[i] + 1 - (i == n) * 2)),mult(dp[i - 1][1],max(0,s[i] - (i == n) * 2)));
            dp[i][1] = add(mult(dp[i - 1][0],(b - 1 - s[i])),mult(dp[i - 1][1],(b - s[i])));
        }else{
            if(sum[i] == 3 * (b + 1)){
                int fst,snd;

                ///no t
               
                if((s[i] - diff[i]) % 2 != 0){
                    printf("0\n");
                    return 0;
                }

                snd = (s[i] - diff[i]) / 2;
                fst = snd + diff[i];

                if(ok(i,fst,snd,s[i],0)){
                    if(fst + snd > b){
                        dp[i][1] = dp[i - 1][0];    
                    }else{
                        dp[i][0] = dp[i - 1][0];    
                    }
                }

                ///with t
                
                snd = (s[i] - diff[i] - 1) / 2;
                fst = snd + diff[i];
                if(ok(i,fst,snd,s[i],1)){
                    if(fst + snd > b){
                        dp[i][1] = dp[i - 1][1];    
                    }else{
                        dp[i][0] = dp[i - 1][1];    
                    }
                }
            }else if(diff[i] == 3 * (b + 1)){
                if(sum[i] % b == s[i]){
                    dp[i][0] = add(mult(dp[i - 1][0],max(0,s[i] + 1 - (i == n) * 2)),mult(dp[i - 1][1],0));
                    dp[i][1] = add(mult(dp[i - 1][0],(b - 1 - s[i])),mult(dp[i - 1][1],0));
                }else{
                    dp[i][0] = add(mult(dp[i - 1][0],0),mult(dp[i - 1][1],max(0,s[i] - (i == n) * 2)));
                    dp[i][1] = add(mult(dp[i - 1][0],0),mult(dp[i - 1][1],(b - s[i])));
                }
            }else{
                if((sum[i] + diff[i]) % 2 != 0){
                    printf("0\n");
                    return 0;
                }
                int fst = (sum[i] + diff[i]) / 2;
                int snd = (sum[i] - diff[i]) / 2;
                if(ok(i,fst,snd,s[i],0)){
                    if(fst + snd > b){
                        dp[i][1] = dp[i - 1][0];
                    }else{
                        dp[i][0] = dp[i - 1][0];
                    }
                }else if(ok(i,fst,snd,s[i],1)){
                    if(fst + snd > b){
                        dp[i][1] = dp[i - 1][1];
                    }else{
                        dp[i][0] = dp[i - 1][1];
                    }
                }
            }
        }
    }

    printf("%d\n",dp[n][0]);
   
    return 0;
}
