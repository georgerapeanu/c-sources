#include <cstdio>
using namespace std;
FILE *f=fopen("pepsi.in","r");
FILE *g=fopen("pepsi.out","w");
int N,M,K,i,j,ultim[150],moment[150],sol[1050],insemn[150],sticla,nr;
bool folosit[150];
char risip[1050];
int main()
{
    fscanf(f,"%d%d%d\n",&N,&M,&K);
    fgets(risip+1,1050,f);
    for(i=1;i<=M;i++)
        {
            moment[i]=K;
            fscanf(f,"%d",&ultim[i]);
        }
    for(i=1;i<=N;i++)
    {
        if(risip[i]=='R')
        {
            sticla=0;
            nr=0;
            for(j=1;j<=M&&nr!=K;j++)
            {
                if(moment[j]>nr)
                {
                    nr=moment[j];
                    sticla=j;
                }
            }
        }
        else
        {
            sticla=0;
            nr=K+1;
            for(j=1;j<=M&&nr!=1;j++)
            {
                if(moment[j]<nr&&moment[j]!=0)
                {
                    nr=moment[j];
                    sticla=j;
                }
            }
        }
        moment[sticla]--;
        sol[i]=sticla;
    }
    for(i=1;i<=M;i++)
    {
        if(moment[i]==ultim[i]&&folosit[i]==0)
        {
            insemn[i]=i;
            folosit[i]=1;
        }
        else
        {
            for(j=1;j<=M&&!insemn[i];j++)
            {
                if(folosit[j]==0&&moment[i]==ultim[j])
                {
                    insemn[i]=j;
                    folosit[j]=1;
                }
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        fprintf(g,"%d ",insemn[sol[i]]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
