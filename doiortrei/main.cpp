#include <cstdio>
using namespace std;
FILE *f=fopen("doitrei.in","r");
FILE *g=fopen("doitrei.out","w");
int V[210],n,i,j,tmp[210];
void shr()
{
    for(int i=V[0]+1;i>1;i--)
    V[i]=V[i-1];
    V[1]=0;
    V[0]++;
}
void shl()
{
    for(int i=1;i<V[0];i++)
    {
        V[i]=V[i+1];
    }
    V[0]--;
}
void inmultire(int Y[],int X[])
{
    for(i=1;i<=Y[0]+X[0]-1;i++)
    {
        shr();
    }
    for( i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            V[i+j-1]+=X[i]*Y[j];
        }
    }
    for(i=V[0];i>1;i--)
    {
        V[i-1]+=V[i]/10;
        V[i]%=10;
    }
    while(V[1]>9)
    {
        shl();
        V[1]+=V[2]/10;
        V[2]%=10;
    }
    while(!V[0])
    shl();
}
int main()
{
    fscanf(f,"%d",&n);
    tmp[0]=n;
    tmp[1]=2;
    for(i=2;i<=n;i++)
    {tmp[i]=3;}
    inmultire(tmp,tmp);
    for(i=1;i<=V[0];i++)
    fprintf(g,"%d",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
