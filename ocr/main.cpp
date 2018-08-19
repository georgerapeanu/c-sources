#include <cstdio>
#include <cmath>
using namespace std;
FILE *f,*g;
int n,m,i,j,x,y;
double M[60][60],minim,nr;
int main()
{
    f=fopen("ocr.in","r");
    fscanf(f,"%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            fscanf(f,"%lf",&nr);
            M[i][j]=M[i-1][j]+M[i][j-1]-M[i-1][j-1]+nr;
        }
    }
    minim=M[n-1][m];x=n;
    for(i=n-1;i>=1;i--)
    {
        if(abs(M[i-1][m]-(M[n][m]-M[i][m]))<minim)
        {
            minim=abs(M[i-1][m]-(M[n][m]-M[i][m]));
            x=i;
        }
    }
    minim=M[n][m-1];y=m;
    for(i=m-1;i>=1;i--)
    {
        if(abs(M[n][i-1]-(M[n][m]-M[n][i]))<minim)
        {
            minim=abs(M[n][i-1]-(M[n][m]-M[n][i]));
            y=i;
        }
    }
    fclose(f);
    g=fopen("ocr.out","w");
    if(x!=25||y!=1)
    fprintf(g,"%d %d",x,y);
    else
        fprintf(g,"26 1");
    fclose(g);
    return 0;
}
