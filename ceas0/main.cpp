#include <cstdio>
using namespace std;
FILE *f=fopen("ceas.in","r");
FILE *g=fopen("ceas.out","w");
double x,V[105];
unsigned long long cmmmc,cmmdc,prod;
int i,j,y,N,r;
unsigned long long nr;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lf",&V[i]);
        if(!cmmmc)
            cmmmc=V[i];
        else
        {
            prod=cmmmc*V[i];
            cmmdc=V[i];
             r=cmmmc%cmmdc;
            while(r)
            {
                cmmmc=cmmdc;
                cmmdc=r;
                r=cmmmc%cmmdc;
            }
            cmmmc=prod/cmmdc;
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=i+1;j<=N;j++)
        {
           x=V[i]*V[j]/(V[j]-V[i]);
           y=1;
            while(y!=int(x*y/V[i])-int(x*y/V[j]))
                y++;
            x*=y;
            nr+=cmmmc/x-1;
        }
    }
    fprintf(g,"%llu",nr);
    fclose(f);
    fclose(g);
    return 0;
}
