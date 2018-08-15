#include <cstdio>
#include <algorithm>
#define MOD 2011
using namespace std;
FILE *f=fopen("minusk.in","r");
FILE *g=fopen("minusk.out","w");
int C[1000005][2],N,K,i,putere2=1;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=K-1;i++)
    {
        C[i][1]=C[i][0]=putere2;
        C[K][0]+=C[i][1];
        putere2*=2;
        putere2%=MOD;
    }
    C[K][1]=(C[K-1][1]+C[K-1][0])%MOD;
    for(i=K+1;i<=N;i++)
    {
        C[i][1]=(C[i-1][1]+C[i-1][0])%MOD;
        C[i][0]=(C[i-1][1]+C[i-1][0]-C[i-K][1])%MOD;
        if(C[i][0]<MOD)
            C[i][0]=C[i][0]%MOD+MOD;
    }

    fprintf(g,"%d",(C[N][1]+C[N][0])%MOD);
    fclose(f);
    fclose(g);
    return 0;
}
