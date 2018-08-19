#include <cstdio>
#define MIN(A,B) A<B ? A:B
using namespace std;
FILE *f,*g;
int a[200][200];
int s[200][200],n,m,i,j,maxim;
int main()
{
    f=fopen("submatrice.in","r");
    fscanf(f,"%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
            fscanf(f,"%d",&a[i][j]);
    }
    fclose(f);
    for(i=1;i<=n;i++)
    s[i][1]=a[i][1];
    for(j=1;j<=m;j++)
    s[1][j]=a[1][j];
    for(i=2;i<=n;i++)
    {
        for(j=2;j<=m;j++)
        {
            if(a[i][j]==1)
            {
                s[i][j]=MIN(s[i][j-1],s[i-1][j]);
                s[i][j]=MIN(s[i][j],s[i-1][j-1]);
                s[i][j]+=1;
                maxim=maxim>s[i][j] ? maxim:s[i][j];
            }
            else
            s[i][j]=0;
        }
    }
    g=fopen("submatrice.out","w");
    fprintf(g,"%d",maxim);
    fclose(g);
    return 0;
}
