#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("purice2.in","r");
FILE *g=fopen("purice2.out","w");
int T,N,a,rez,i,j,rest,V[60],k;
int main()
{
    fscanf(f,"%d",&T);
    for(i=1;i<=T;i++)
    {
        fscanf(f,"%d",&N);
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%d",&V[j]);
        }
        rez=0;
        for(j=1;j<=N&&rez!=1;j++)
        {
            for(k=j+1;k<=N&&rez!=1;k++)
            {
                a=abs(V[k]-V[j]);
                rest=rez%a;
                while(rest)
                {
                    rez=a;
                    a=rest;
                    rest=rez%a;
                }
                rez=a;
            }
        }
        if(rez==1)
            fprintf(g,"1\n");
        else
            fprintf(g,"0\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
