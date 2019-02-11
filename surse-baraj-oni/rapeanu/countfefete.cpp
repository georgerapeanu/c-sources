#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("countfefete.in","r");
FILE *g = fopen("countfefete.out","w");
int dp[200005][35][2];
int trec[35][2];
int tmp[35][2];
bool activ[200005];
int N;
vector<int> G[200005];
pair<int,int> V[200005];
int T[200005];
int SZ[200005];
int rez;
const int MOD = (1e9) + 7;
int adun(int a,int b){
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
int fi(int x){
    if(!T[x]){
        return x;
    }
    return x = fi(T[x]);
}
void u(int x,int y){
    x = fi(x);
    y = fi(y);
    SZ[y] += SZ[x];
    T[x] = y;
}
int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        SZ[i] = 1;
        fscanf(f,"%d",&V[i].first);
        V[i].second = i;
    }
    for(int i = 1;i < N;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    sort(V + 1,V + 1 + N);
    reverse(V + 1,V + 1 + N);
    for(int i = 1;i <= N;i++){
        int nod = V[i].second;
        int val = V[i].first;
        for(int bit = 0;bit <= 30;bit++){
            trec[bit][0] = trec[bit][1] = 0;
        }
        ///nu il luam
        for(auto it2:G[nod]){
            if(activ[it2]){
                int it = fi(it2);
                for(int bit = 0;bit <= 30;bit++){
                    int a = dp[nod][bit][0];
                    int b = dp[nod][bit][1];
                    trec[bit][1] = scad(trec[bit][1],dp[it][bit][1]);
                    trec[bit][0] = scad(trec[bit][0],dp[it][bit][0]);
                    dp[nod][bit][0] = (1LL * (a + 1) * (dp[it][bit][0] + 1) - 1 + 1LL * (b) * (dp[it][bit][1])) % MOD;
                    dp[nod][bit][1] = (1LL * b * (dp[it][bit][0] + 1) + 1LL * (a + 1) * dp[it][bit][1]) % MOD;
                }
                u(it,nod);
            }
        }
        /// il luam
        for(int bit = 0;bit <= 30;bit++){
            int a = dp[nod][bit][0];
            int b = dp[nod][bit][1];
            dp[nod][bit][0 ^ ((val >> bit) & 1)] = adun(dp[nod][bit][0 ^ ((val >> bit) & 1)],a);
            dp[nod][bit][1 ^ ((val >> bit) & 1)] = adun(dp[nod][bit][1 ^ ((val >> bit) & 1)],b);
            dp[nod][bit][(val >> bit) & 1] = adun(dp[nod][bit][(val >> bit) & 1],1);
        }
        for(int bit = 0;bit <= 30;bit++){
            trec[bit][1] = adun(trec[bit][1],dp[nod][bit][1]);
            trec[bit][0] = adun(trec[bit][0],dp[nod][bit][0]);
            rez = adun(rez,1LL * trec[bit][!((val >> bit) & 1)] * lgpow(2,bit) % MOD);
        }
        activ[nod] = 1;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}

