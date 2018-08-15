#include <cstdio>
using namespace std;
FILE *f=fopen("input.in","r"),*g=fopen("output.out","w");
void triunghi()
{
    int m[101][101],i,j,s[101][101];
    for(i=0;i<=100;i++)
    for(j=0;j<=100;j++)
    m[i][j]=s[i][j]=0;
    for(i=1;i<=5;i++)
    for(j=1;j<=i;j++)
    {
        fscanf(f,"%d",&m[i][j]);
        s[i][j]=m[i][j];
    }
    for(i=5;i>=1;i--)
    {
        for(j=1;j<=i;j++)
        {
            s[i][j]+=(s[i+1][j]>s[i+1][j+1] ? s[i+1][j]:s[i+1][j+1]);
        }
    }
    fprintf(g,"%d",s[1][1]);
}
void subsir()
{
     int n,m,k,l,x[100]={0},y[100]={0};
     int s[100][100]={0};
     fscanf(f,"%d %d",&n,&m);
     for(k=1;k<=n;k++)
        fscanf(f,"%d",&x[k]);
     for(k=1;k<=m;k++)
        fscanf(f,"%d",&y[k]);
     for(k=1;k<=n;k++)
     {
         for(l=1;l<=m;l++)
         {
             if(x[k]==y[l])
             {
                  s[k][l]=s[k-1][l-1]+1;
             }
             else
             {
                 s[k][l]=s[k-1][l]>s[k][l-1] ? s[k-1][l]:s[k][l-1];
             }
         }
     }
     fprintf(g,"%d",s[n][m]);
}
int main()
{
    subsir();
    return 0;
}
