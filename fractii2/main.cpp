#include <cstdio>
#define MOD 100003
using namespace std;
FILE *f=fopen("fractii2.in","r");
FILE *g=fopen("fractii2.out","w");
int c;
int N,i;
int j,M,S;
int D[2005][2005];
int main()
{
    fscanf(f,"%d %d",&c,&N);
    if(c==1)
    {
        for(i=1;i<N;i++)
            fprintf(g,"%d ",i);
        fprintf(g,"%d",i-1);
    }
    else
    {
        D[2][1]=1;
        for(i=3;i<=N;i++)
        {
            M=i/2;
            for(j=1;j<=M;j++)
            {
                D[i][j]=D[i][j-1]+D[i-j][(i-j)/2]-D[i-j][(j+1)/2-1];
                D[i][j]%=MOD;
                if(D[i][j]<0)
                    D[i][j]+=MOD;
            }
        }
        fprintf(g,"%d",D[N][N/2]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
