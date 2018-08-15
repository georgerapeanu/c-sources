#include <cstdio>
using namespace std;
short i,j,t[251][251],n,m,suma[40001],op,coo,maxi;
int dim[15626],s;
bool uz[40001][251],a;
void fill(int x,int y,int k)
{
    if(t[x][y]==1)
    {
        t[x][y]=k+1;
        dim[k]++;
        fill(x+1,y,k);
        fill(x+1,y+1,k);
        fill(x,y+1,k);
        fill(x-1,y+1,k);
        fill(x-1,y,k);
        fill(x-1,y-1,k);
        fill(x,y-1,k);
        fill(x+1,y-1,k);
    }
}
int main()
{
    FILE *f,*g;
    f=fopen("parcela.in","r");
    fscanf(f,"%hd %hd %d",&m,&n,&s);
    for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
    fscanf(f,"%hd",&t[i][j]);
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(t[i][j]==1)
            {fill(i,j,++dim[0]);}
        }
    }
    for(i=1;i<=s;i++)
    {
        op=0;coo=0;
        for(j=1;j<=dim[0];j++)
        {
            if(dim[j]<=i&&uz[i-dim[j]][j]==0)
            {
                    if(suma[i-dim[j]]+dim[j]>op)
                    {
                        op=suma[i-dim[j]]+dim[j];coo=j;
                    }
            }
        }
        if(op==0)
        suma[i]=0;
        else
        {
            suma[i]=suma[i-dim[coo]]+dim[coo];
            for(j=1;j<=dim[0];j++)
            {
                uz[i][j]=uz[i-dim[coo]][j];
            }
            uz[i][coo]=1;
            if(suma[i]>maxi)
            maxi=suma[i];
        }
    }
    g=fopen("parcela.out","w");
    fprintf(g,"%hd",maxi);
    fclose(g);
    return 0;
}
