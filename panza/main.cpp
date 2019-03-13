#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("panza.in","r");
FILE *g = fopen("panza.out","w");

const int NMAX = 1e5;
const int MMAX = 1e5;
const int PMAX = 1e6;
const long long inf = 1e17;

int n,m,st,dr;
int a[MMAX + 5];
int x[MMAX + 5];
int y[MMAX + 5];
long long dp[MMAX + 5];

void propag(){
    for(int j = 2;j <= m;j++){
        dp[j] = min(dp[j],dp[j - 1] + 1);
    }
    for(int j = m - 1;j;j--){
        dp[j] = min(dp[j],dp[j + 1] + 1);
    }
}

int main(){

    fscanf(f,"%d %d %d %d",&n,&m,&st,&dr);

    for(int i = 1;i <= m;i++){
        fscanf(f,"%d",&a[i]);
        if(i > 1){
            a[i] = min(a[i],a[i - 1] + 2);
        }
    }

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&x[i],&y[i]);
    }

    for(int i = 1;i <= m;i++){
        dp[i] = inf;
    }

    dp[st] = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            dp[j] = dp[j] + a[j] * (i > 1);
        }

        propag();

        for(int j = 1;j < x[i];j++){
            dp[j] = inf;
        }
        for(int j = y[i] + 1;j <= m;j++){
            dp[j] = inf;
        }

        propag();
    }

    fprintf(g,"%lld\n",dp[dr]);

    fclose(f);
    fclose(g);

    return 0;
}
