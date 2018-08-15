#include <cstdio>
using namespace std;
FILE *f,*g;
int cer;
int m,n,ma[181][181],pmax[181][181],i,j,r,c,t,l1,c1,l2,c2,k,maxi;
int min(int a,int b,int c0)
{
    if(a<b&&a<c0)return a;
    if(b<c0)return b;
    return c0;
}
int main()
{
    f=fopen("teren1.in","r");
    fscanf(f,"%d",&cer);
    fscanf(f,"%d %d %d %d %d",&n,&m,&t,&r,&c);
    for(i=1;i<=t;i++)
    {
        fscanf(f,"%d %d %d %d",&l1,&c1,&l2,&c2);
        for(j=l1;j<=l2;j++)
        {
            for(k=c1;k<=c2;k++)
            {
                ma[j][k]++;
                if(ma[j][k]>maxi)
                maxi=ma[j][k];
            }
        }
    }
    fclose(f);
    g=fopen("teren1.out","w");
    if(cer==1)
    fprintf(g,"%d",ma[r][c]);
    else if(cer==2)
    fprintf(g,"%d",maxi);
    else
    {
        maxi=0;
        for(i=1;i<=n;i++)
        {
            if(ma[i][1]==0)
            {
                maxi=1;
                pmax[i][1]=1;
            }
        }
        for(i=1;i<=m;i++)
          if(ma[1][i]==0)
            {
                maxi=1;
                pmax[1][i]=1;
            }
        for(i=2;i<=n;i++)
        {
            for(j=2;j<=m;j++)
            {
                if(ma[i][j]==0)
                {
                    pmax[i][j]=min(pmax[i-1][j],pmax[i-1][j-1],pmax[i][j-1])+1;
                    if(pmax[i][j]>maxi)
                    maxi=pmax[i][j];
                }
            }
        }
        fprintf(g,"%d",maxi*maxi);
    }
    fclose(g);
    return 0;
}
