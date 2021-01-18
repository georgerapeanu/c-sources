#include <cstdio>

using namespace std;

struct query_t{
    int s,t,val_s,val_t;
    int ans;
};

const int NMAX = 60;
const int KMAX = 60;
const int QMAX = 60;
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

int n,k,q;
int adj[NMAX + 2 * QMAX + 1][NMAX + 2 * QMAX + 1];
int dp[KMAX + 1][NMAX + 2 * QMAX + 1][NMAX + 2 * QMAX + 1];
int value_lock[NMAX + 2 * QMAX + 1];

char tmp[NMAX + 10];
query_t queries[QMAX + 1];
int left_weight[NMAX + 2 * QMAX + 5];
int right_weight[NMAX + 2 * QMAX + 5];

int main(){

    scanf("%d %d %d\n",&n,&k,&q);
    k--;

    for(int i = 1;i <= n;i++){
        fgets(tmp + 1,n + 5,stdin);
        value_lock[i] = -1;

        for(int j = 1;j <= n;j++){
            adj[i][j] = tmp[j] - '0';          
        }
    }

    int old_n = n;

    for(int i = 1;i <= q;i++){
        scanf("%d %d %d %d\n",&queries[i].val_s,&queries[i].s,&queries[i].val_t,&queries[i].t);
        queries[i].ans = (queries[i].val_s == queries[i].val_t && queries[i].s == queries[i].t);
        queries[i].val_s--;
        queries[i].val_t--;
        ++n;
        for(int j = 1;j <= n;j++){
            adj[n][j] = adj[queries[i].s][j];
        }
        queries[i].s = n;
        value_lock[n] = queries[i].val_s;
        ++n;
        for(int j = 1;j <= n;j++){
            adj[j][n] = adj[j][queries[i].t];
        }
        queries[i].t = n;
        value_lock[n] = queries[i].val_t;
    }

    for(int h = 0;h <= k;h++){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(h > 0){
                    dp[h][i][j] = add(dp[h][i][j],dp[h - 1][i][j]);
                }
            }
        }

        for(int r = 1;r <= n;r++){
            if(value_lock[r] != -1 && value_lock[r] != h){
                continue;
            }
            for(int i = 1;i <= n;i++){
                left_weight[i] = right_weight[i] = 0;
            }
            if(h > 0){
                for(int b = 1;b <= n;b++){
                    if(adj[b][r] == 1){
                        for(int a = 1;a <= n;a++){
                            left_weight[a] = add(left_weight[a],dp[h - 1][a][b]);
                        }
                    } 
                }
            }
            left_weight[r] = add(left_weight[r],1);
            if(h > 0){
                for(int c = 1;c <= n;c++){
                    if(adj[r][c] == 1){
                        for(int d = 1;d <= n;d++){
                            right_weight[d] = add(right_weight[d],dp[h - 1][c][d]);
                        }
                    }
                }
            }
            right_weight[r] = add(right_weight[r],1);
            for(int a = 1;a <= n;a++){
                for(int b = 1;b <= n;b++){
                    dp[h][a][b] = add(dp[h][a][b],mult(left_weight[a],right_weight[b]));
                }
            }
        }
    }

    for(int i = 1;i <= q;i++){
        printf("%d\n",add(dp[k][queries[i].s][queries[i].t],queries[i].ans));
    }

    return 0;
}
