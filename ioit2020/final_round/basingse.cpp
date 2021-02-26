#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int KMAX = 1e3;
const int inf = 1e9;
const int XMAX = 30;

int n,x,changes;
int dp[NMAX + 1][KMAX + 1][2];
int tmp_dp[KMAX + 1][2];
int len[NMAX + 5];
int v[NMAX + 5];

long long bit_dp[XMAX + 1][KMAX + 1];
int bit_len[XMAX + 1];
long long bit_tmp[KMAX + 1];

vector<int> graph[NMAX + 5];

void dfs(int h,int nod,int tata){
    
    len[nod] = 1;
    dp[nod][0][((v[nod] >> h) & 1)] = 0;
    dp[nod][0][!((v[nod] >> h) & 1)] = -inf;
    dp[nod][1][!((v[nod] >> h) & 1)] = 0;
    dp[nod][1][((v[nod] >> h) & 1)] = -inf;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(h,it,nod);
        
        for(int j = 0;j <= len[nod] + len[it] && j <= changes;j++){
            tmp_dp[j][0] = tmp_dp[j][1] = -inf;
        }

        for(int j = 0;j <= len[nod];j++){
            for(int k = 0;k <= len[it] && j + k <= changes;k++){
                tmp_dp[j + k][0] = max(tmp_dp[j + k][0],dp[nod][j][0] + max(dp[it][k][0],dp[it][k][1]));
                tmp_dp[j + k][1] = max(tmp_dp[j + k][1],dp[nod][j][1] + max(dp[it][k][0],1 + dp[it][k][1]));
            }
        }
        len[nod] += len[it];
        len[nod] = min(len[nod],changes);
        for(int j = 0;j <= len[nod];j++){
            dp[nod][j][0] = tmp_dp[j][0];
            dp[nod][j][1] = tmp_dp[j][1];
        }
    }
}

int main(){

    scanf("%d %d %d",&n,&x,&changes);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i < n;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int h = x - 1;h >= 0;h--){
        dfs(h,1,0);
        for(int i = 0;i <= len[1];i++){
            bit_dp[h][i] = max(dp[1][i][0],dp[1][i][1]) * (1LL << h);
        }
        bit_len[h] = len[1];
        printf("deb %d\n",h);
        for(int i = 0;i <= len[1];i++){
            printf("%lld ",bit_dp[h][i] >> h);
        }
        printf("\n");
    }

    for(int h = 1;h < x;h++){
        for(int j = 0;j <= bit_len[h - 1] + bit_len[h] && j <= changes;j++){
            bit_tmp[j] = -inf;    
        }
        for(int j = 0;j <= bit_len[h - 1];j++){
            for(int k = 0;k <= bit_len[h] && j + k <= changes;k++){
                bit_tmp[j + k] = max(bit_tmp[j + k],bit_dp[h - 1][j] + bit_dp[h][k]);
            }
        }
        bit_len[h] += bit_len[h - 1];
        bit_len[h] = min(bit_len[h],changes);
        
        for(int j = 0;j <= bit_len[h];j++){
            bit_dp[h][j] = bit_tmp[j];
        }
    }

    long long ans = 0;

    for(int i = 0;i <= bit_len[x - 1];i++){
        ans = max(ans,bit_dp[x - 1][i]);
    }

    printf("%lld\n",ans);

    return 0;
}
