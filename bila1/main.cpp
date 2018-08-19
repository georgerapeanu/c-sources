#include <cstdio>
#include <cstdlib>
using namespace std;
FILE *f,*g;
short v[2001],m,n,p,i,x,y,j;
short tab[2001][2001];
int main()
{
    f=fopen("bile1.in","r");
    fscanf(f,"%hd %hd %hd",&m,&n,&p);
    for(i=1;i<=p;i++)
    {
        fscanf(f,"%hd %hd",&x,&y);
        tab[x][0]++;
        tab[x][tab[x][0]]=y;
    }
    for(i=1;i<=n;i++)
    fscanf(f,"%hd",&v[i]);
    fclose(f);
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=tab[i][0];j++)
        {
            if(v[tab[i][j]]%2==0)
            {
                 v[tab[i][j]-1]+=v[tab[i][j]]/2;
                 v[tab[i][j]+1]+=v[tab[i][j]]/2;
                 v[tab[i][j]]=0;
            }
            else
            {
                v[tab[i][j]-1]+=v[tab[i][j]]/2+1;
                v[tab[i][j]+1]+=v[tab[i][j]]/2;
                v[tab[i][j]]=0;
            }
        }
    }
    g=fopen("bile1.out","w");
    for(i=1;i<=n;i++)
    fprintf(g,"%hd\n",v[i]);
    fclose(g);
    return 0;
}
