#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("ausoara.in","r");
FILE *g=fopen("ausoara.out","w");
int T,N,V,LCD[1005],i,j,tmp[1005],ctr;
int main()
{
    fscanf(f,"%d",&T);
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&LCD[i]);
    LCD[0]=N;
    for(i=2;i<=T;i++)
    {
        fscanf(f,"%d",&N);
        ctr=1;
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%d",&V);
            while(V>LCD[ctr]&&LCD[ctr]!=0)
            {
                ctr++;
            }
            if(V==LCD[ctr]&&ctr<=LCD[0])
                {tmp[++tmp[0]]=V;ctr++;}
        }
        for(j=1;j<=tmp[0];j++)
            LCD[j]=tmp[j];
        LCD[0]=tmp[0];
        tmp[0]=0;
    }
    for(i=0;i<=LCD[0];i++)
        fprintf(g,"%d ",LCD[i]);
    fclose(f);
    fclose(g);
    return 0;
}
