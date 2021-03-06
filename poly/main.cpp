#include <cstdio>
#define MODUL 30103
using namespace std;
FILE *f=fopen("poly.in","r");
FILE *g=fopen("poly.out","w");
int C[2][1005],N;
int i,j,ivmodular;
int lgpow(int a,int b)
{
    int p=1;
    while(b)
    {
        if(b%2)
            {p*=a;p%=MODUL;}
        a*=a;
        a%=MODUL;
        b/=2;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&N);
    C[0][1]=1;
    for(i=1;i<=2*N;i++)
    {
        C[i%2][0]=C[i%2][i]=1;
        for(j=1;j<i;j++)
        {
            C[i%2][j]=(C[(i+1)%2][j-1]+C[(i+1)%2][j])%MODUL;
        }
    }
    ivmodular=lgpow(N+1,30101);
    fprintf(g,"%d",(C[0][N]*ivmodular)%MODUL);
    fclose(f);
    fclose(g);
    return 0;
}
