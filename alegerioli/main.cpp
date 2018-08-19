#include <cstdio>
using namespace std;
FILE *f=fopen("alegeri.in","r");
FILE *g=fopen("alegeri.out","w");
int suma[1005],maxim,v[1005],candidat=-1,i,N,j,val,M,s,S;
int main()
{
    fscanf(f,"%d %d",&M,&N);
    for(i=1;i<=N;i++)
    {
        s=0;
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&val);
            s+=val;
            suma[j]+=val;
        }
        if(s==maxim)
            v[++v[0]]=i;
        else if(s>maxim)
        {
            v[0]=1;
            v[1]=i;
            maxim=s;
        }
        S+=s;
    }
    fprintf(g,"%d\n",S);
    for(i=1;i<=v[0];i++)
        fprintf(g,"%d ",v[i]);
    fprintf(g,"\n");
    for(i=1;i<=M&&candidat==-1;i++)
        if(suma[i]>=S/2+1)
            candidat=i;
    fprintf(g,"%d",candidat);
    fclose(f);
    fclose(g);
    return 0;
}
