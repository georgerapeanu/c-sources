#include <cstdio>
using namespace std;
FILE *f=fopen("renju.in","r");
FILE *g=fopen("renju.out","w");
int M[20][20],i,j,castigator;
bool ok(int x,int y,int val)
{
    if(M[x][y]==M[x+1][y+1]&&M[x+1][y+1]==M[x+2][y+2]&&M[x+2][y+2]==M[x+3][y+3]&&M[x+4][y+4]==M[x+3][y+3]&&M[x+4][y+4]==val&&M[x-1][y-1]!=val&&M[x+5][y+5]!=val)
        return 1;
     if(M[x][y]==M[x+1][y]&&M[x+1][y]==M[x+2][y]&&M[x+2][y]==M[x+3][y]&&M[x+4][y]==M[x+3][y]&&M[x+4][y]==val&&M[x-1][y]!=val&&M[x+5][y]!=val)
        return 1;
    if(M[x][y]==M[x][y+1]&&M[x][y+1]==M[x][y+2]&&M[x][y+2]==M[x][y+3]&&M[x][y+4]==M[x][y+3]&&M[x][y+4]==val&&M[x][y-1]!=val&&M[x][y+5]!=val)
        return 1;
    return 0;
}
int main()
{
    for(i=1;i<=19;i++)
    {
        for(j=1;j<=19;j++)
        {
            fscanf(f,"%d",&M[i][j]);
        }
    }
    for(i=1;i<=19&&!castigator;i++)
    {
        for(j=1;j<=19&&!castigator;j++)
        {
            if(M[i][j]==1&&ok(i,j,1))
                castigator=1;
            if(M[i][j]==2&&ok(i,j,2))
            castigator=2;
        }
    }
    fprintf(g,"%d\n",castigator);
    if(castigator)
        fprintf(g,"%d %d",i-1,j-1);
    fclose(f);
    fclose(g);
    return 0;
}
