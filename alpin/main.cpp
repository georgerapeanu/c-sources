#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("alpin.in","r");
FILE *g=fopen("alpin.out","w");
int A[1030][1030],D[1030][1030],maxim,N,i,j,k;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
int  calcul(int x,int y)
{
    D[x][y]=max(max(calcul(x+1,y),calcul(x,y+1)),max(calcul(x-1,y),calcul(x,y-1)));
    return D[x][y];
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%d",&A[i][j]);
        }
    }

    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
