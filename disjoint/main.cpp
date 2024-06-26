#include <cstdio>
using namespace std;
FILE *f=fopen("disjoint.in","r");
FILE *g=fopen("disjoint.out","w");
int nod[100005],a,b,i,N,M,op;
void un(int x,int y)
{
    if(nod[x]<nod[y])
    {nod[x]+=nod[y];nod[y]=x;}
    else
    {nod[y]+=nod[x];nod[x]=y;}
}
int fi(int x)
{
    if(nod[x]<0)
        return x;
    else
    {nod[x]=fi(nod[x]);return nod[x];}
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        nod[i]=-1;
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %d",&op,&a,&b);
        a=fi(a);
        b=fi(b);
        if(op==1)
            un(a,b);
        else
            if(a!=b)
                fprintf(g,"NU\n");
            else
                fprintf(g,"DA\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
