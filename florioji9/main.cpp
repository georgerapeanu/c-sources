#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("flori.in","r");
FILE *g=fopen("flori.out","w");
short V[1005],N,M;
short val[1005];
short a,b,c,d;
bitset<1005> B;
short fi(short x)
{
    if(V[x]<0)
        return x;
    V[x]=fi(V[x]);
    return V[x];
}
void u(short x,short y)
{
    x=fi(x);y=fi(y);
    if(x==y) return;

    if(V[x]<V[y]){V[x]+=V[y];V[y]=x;}
    else{V[y]+=V[x];V[x]=y;}
}
int main()
{
    fscanf(f,"%hd%hd",&N,&M);
    for(short i=0;i<=1000;i++) V[i]=-1;
    for(short i=1;i<=N;i++)
    {
        fscanf(f,"%hd",&val[i]);
        for(short j=2;j<=M;j++)
        {
            fscanf(f,"%hd",&a);
            u(val[i],a);
        }
    }
    for(short i=1;i<=N;i++)
    {
        short tmp=fi(val[i]),nr=0;;
        for(short j=1;j<=N;j++)
            if(!B[j]&&fi(val[j])==tmp)
            {
                fprintf(g,"%hd ",j);
                B[j]=1;
                nr++;
            }
        if(nr)
            fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
