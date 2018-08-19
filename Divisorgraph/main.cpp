#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("divisorgraph.in","r");
FILE *g = fopen("divisorgraph.out","w");
int out[5005];
int in[5005];
int N,T,M;
int EXP[5005];
int len;
bool E[5005];
int P[5005],nrp;
const int MOD = (1e9) + 7;
int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * b * p % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}
int main()
{
    for(int i = 2;i <= 5000;i++){
        if(!E[i]){
            P[++nrp] = i;
            for(int j = i * i;j <= 5000;j += i){
                E[j] = 1;
            }
        }
    }
    fscanf(f,"%d",&T);
    while(T--){
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        fscanf(f,"%d %d",&N,&M);
        if(N == 1){
            fprintf(g,"%d\n",1);
            continue;
        }
        while(M--){
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            out[x]++;
            in[y]++;
        }
        len = 0;
        for(int i = 1;i <= N;i++){
            if(in[i] == 1){
                EXP[++len] = (out[i] + 1) / (N - out[i] - 1);
            }
        }
        sort(EXP + 1,EXP + 1 + len);
        int rez = 1;
        for(int i = 1;i <= len;i++){
            rez = 1LL * rez * lgpow(P[len - i + 1],EXP[i]) % MOD;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
