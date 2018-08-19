#include <cstdio>
using namespace std;
int n,k,m,i,j;
int main()
{
    FILE *f,*g;
    f=fopen("numere2.in","r");
    fscanf(f,"%d",&m);
    g=fopen("numere2.out","w");
    for(i=1;i<=m;i++)
    {
        fscanf(f,"%d",&n);
        k=(n+1)/2;
        for(j=k;j<=k+n-1;j++)
        fprintf(g,"%d ",j);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
