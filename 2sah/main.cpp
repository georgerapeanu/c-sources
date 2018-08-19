#include <cstdio>
#define MOD 100003
using namespace std;
FILE *f=fopen("2sah.in","r");
FILE *g=fopen("2sah.out","w");
int lgpownr(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int p[3][3]={1,0,0,0,1,0,0,0,1};
int mat[3][3]={0,1,0,0,0,1,1,1,1};
int F[3]={1,1,2};
void mult(int a[3][3],int b[3][3])
{
    int tmp[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            tmp[i][j]=0;
            for(int k=0;k<3;k++)
            {
                tmp[i][j]=(tmp[i][j]+1LL*a[i][k]*b[k][j])%MOD;
            }
        }
    }
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=tmp[i][j];
}
void lgpowmat(int e)
{
    while(e)
    {
        if(e&1)mult(p,mat);
        mult(mat,mat);
        e>>=1;
    }
}
int C;
int N,K;
int main()
{
    fscanf(f,"%d%d%d",&C,&N,&K);
    if(C==1)
    {
        fprintf(g,"%d",lgpownr(3,K-1));
    }
    else
    {
        if(N-K+1<0){fputc('0',g);return 0;}
        if(N-K+1<=2){fprintf(g,"%d",F[N-K+1]);return 0;}
        lgpowmat(N-K-1);
        fprintf(g,"%d",(1LL*F[0]*p[2][0]+1LL*F[1]*p[2][1]+1LL*F[2]*p[2][2])%MOD);
    }
    fclose(f);
    fclose(g);
    return 0;
}
