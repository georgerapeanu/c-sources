#include <cstdio>
#define MOD 29997
using namespace std;
FILE *f=fopen("doipe.in","r");
FILE *g=fopen("doipe.out","w");
int T,N,DP[2][2005],i,j;
char C[2005];
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d\n",&N);
        fgets(C+1,2005,f);
        DP[1][1]=1;
        for(i=2;i<=N;i++)
        {
            for(j=1;j<=i;j++)
            {
                DP[i%2][j]=DP[i%2][j-1];
                if(C[i-1]=='<')
                {
                    DP[i%2][j]=(DP[i%2][j]+DP[(i-1)%2][j-1])%MOD;
                }
                else
                {
                    DP[i%2][j]=(DP[i%2][j]+DP[(i-1)%2][i-1]-DP[(i-1)%2][j-1])%MOD;
                    if(DP[i%2][j]<0)
                        DP[i%2][j]=DP[i%2][j]%MOD+MOD;
                }
            }
        }
        T--;fprintf(g,"%d\n",DP[N%2][N]);
    }
    return 0;
}
