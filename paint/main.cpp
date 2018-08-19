#include <cstdio>
using namespace std;
FILE *f=fopen("paint.in","r");
FILE *g=fopen("paint.out","w");
int m[1005][1005],N,M,Q,l1,c1,l2,c2,i,j,exponent,rez,a;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&m[i][j]);
            m[i][j]=m[i-1][j]+m[i][j-1]-m[i-1][j-1]+1-m[i][j];
        }
    }
    fscanf(f,"%d",&Q);
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%d %d %d %d",&l1,&c1,&l2,&c2);
        exponent=m[l2][c2]+m[l1-1][c1-1]-m[l1-1][c2]-m[l2][c1-1];
        rez=1;
        a=2;
        while(exponent)
        {
            if(exponent&1)
                rez=(rez*a)%1001;
            a=(a*a)%1001;
            exponent/=2;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
