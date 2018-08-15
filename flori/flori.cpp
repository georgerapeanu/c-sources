#include <cstdio>
using namespace std;
FILE *f,*g;
int i,j,m[1000][1000],n,m1,z,l1,l2,c1,c2,x,maxim,nrmax,k;
int main()
{
    f=fopen("flori.in","r");
    fscanf(f,"%d %d",&n,&m1);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m1;j++)
        {
            fscanf(f,"%d",&m[i][j]);
            if(m[i][j]>maxim)
            {
                maxim=m[i][j];
                nrmax=1;
            }
            else if(m[i][j]==maxim)
            {
                nrmax++;
            }
        }
    }
    fscanf(f,"%d",&z);
    for(i=1;i<=z;i++)
    {
        fscanf(f,"%d %d %d %d %d",&l1,&c1,&l2,&c2,&x);
        for(j=l1;j<=l2;j++)
        {
            for(k=c1;k<=c2;k++)
            {
                m[j][k]+=x;
            if(m[j][k]>maxim)
            {
                maxim=m[j][k];
                nrmax=1;
            }
            else if(m[j][k]==maxim)
            {
                nrmax++;
            }
            }
        }
    }
    fclose(f);
    g=fopen("flori.out","w");
    fprintf(g,"%d %d",maxim,nrmax);
    fclose(g);
    return 0;
}
