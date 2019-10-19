#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;

int t;
int n;
bool has_a[300];
bool has_b[300];
bool has_c[300];
int dp[200][200][200][3][2];

void add_to(int a,int b,int c,int turn,int des,int val){
    if(0 <= a && 0 <= b && 0 <= c && 0 <= turn && turn <= 2 && 0 <= des && des <= 1){
        dp[a][b][c][turn][des] += val;
        if(dp[a][b][c][turn][des] >= MOD){
            dp[a][b][c][turn][des] -= MOD;
        }
    }
}

int main(){
    
    scanf("%d %d",&n,&t);

    while(t--){
        memset(dp,0,sizeof(dp));
        for(int i = 1;i <= 2 * n;i++){
            int val;
            scanf("%d",&val);
            has_a[val] = true;
        }
        
        for(int i = 1;i <= 2 * n;i++){
            int val;
            scanf("%d",&val);
            has_b[val] = true;
        }
        
        for(int i = 1;i <= 2 * n;i++){
            int val;
            scanf("%d",&val);
            has_c[val] = true;
        }

        int ab = 0,bc = 0,ca = 0;
        
        for(int i = 1;i <= 3 * n;i++){
            if(has_a[i] && has_b[i])ab++;
            if(has_b[i] && has_c[i])bc++;
            if(has_c[i] && has_a[i])ca++;
            has_a[i] = false;
            has_b[i] = false;
            has_c[i] = false;
        }

        dp[ab][bc][ca][0][0] = 1;

        for(int sum = ab + bc + ca;sum > 0;sum--){
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///A turn & true
                    add_to(a - 1,b,c,1,true,1LL * dp[a][b][c][0][true] * a % MOD) ;
                    add_to(a,b + 1,c - 1,1,true,1LL * dp[a][b][c][0][true] * c % MOD);
                    if(a + c == 0){
                        add_to(a,b,c,1,true,dp[a][b][c][0][true]);
                    }
                }
            }
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///B turn & true
                    add_to(a,b - 1,c,2,true,1LL * dp[a][b][c][1][true] * b % MOD);
                    add_to(a - 1,b,c + 1,2,true,1LL * dp[a][b][c][1][true] * a % MOD);
                    if(a + b == 0){
                        add_to(a,b,c,2,true,dp[a][b][c][1][true]);
                    }
                }
            }
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///C turn & true
                    add_to(a,b,c - 1,0,false,1LL * dp[a][b][c][2][true] * c % MOD);
                    add_to(a + 1,b - 1,c,0,false,1LL * dp[a][b][c][2][true] * b % MOD);
                    if(b + c == 0){
                        add_to(a,b,c,0,false,dp[a][b][c][2][true]);
                    }
                }
            }
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///A turn & false
                    add_to(a - 1,b,c,1,true,1LL * dp[a][b][c][0][false] * a % MOD);
                    add_to(a,b + 1,c - 1,1,false,1LL * dp[a][b][c][0][false] * c % MOD);
                    if(a + c == 0){
                        add_to(a,b,c,1,false,dp[a][b][c][0][false]);
                    }
                }
            }
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///B turn & false
                    add_to(a,b - 1,c,2,true,1LL * dp[a][b][c][1][false] * b % MOD);
                    add_to(a - 1,b,c + 1,2,false,1LL * dp[a][b][c][1][false] * a % MOD);
                    if(a + b == 0){
                        add_to(a,b,c,2,false,dp[a][b][c][1][false]);
                    }
                }
            }
            for(int a = 0;a <= sum;a++){
                for(int b = 0;b <= sum - a;b++){
                    int c = sum - a - b;
                    ///C turn & false
                    add_to(a,b,c - 1,0,false,1LL * dp[a][b][c][2][false] * c % MOD);
                }
            }
        }

        int ans = 0;

        for(int t = 0;t < 3;t++){
            for(int d = 0;d < 2;d++){
                ans = (ans + dp[0][0][0][t][d]);
                if(ans >= MOD){
                    ans -= MOD;
                }
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
