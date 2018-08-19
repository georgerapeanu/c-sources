#include <cstdio>
using namespace std;
FILE *f=fopen("cruce.in","r");
FILE *g=fopen("cruce.out","w");
int N,M,K1,K2,nr;
char C[105][105];
int  gvert(int c,int x,int y)
{
    if(!x||y>N)
        return 0;
    if(C[x][c]==C[y][c])
        return 1+gvert(c,x-1,y+1);
    return 0;
}
int gor(int l,int x,int y)
{
    if(!x||y>M)
        return 0;
    if(C[l][x]==C[l][y])
        return 1+gor(l,x-1,y+1);
    return 0;
}
int main()
{
    fscanf(f,"%d%d\n",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fgets(C[i]+1,105,f);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            K1=gvert(j,i,i);
            K2=gor(i,j,j);
            nr+=(K1-1)*(K2-1);
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
