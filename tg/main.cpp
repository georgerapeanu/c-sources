#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("tg.in","r");
FILE *g=fopen("tg.out","w");
int X[4000005];
int i,j;
int A,B,C;
int N,k,lim;
long long nr;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N-2;i++)
    {
        if(!X[i])
        {
            for(j=1;i*j*j<=N;j++)
            {
                X[i*j*j]=i;
            }
        }
    }
    for(A=1;A<=N-2;A++)
    {
        lim=(int)sqrt(N/X[A]);
        nr+=lim-(int)sqrt(A/X[A]);
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
