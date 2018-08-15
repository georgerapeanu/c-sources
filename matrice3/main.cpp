#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("matrice3.in","r");
FILE *g=fopen("matrice3.out","w");
unsigned char dp[9][9][255][255];
unsigned char D[255][255];
int i,j,N,M,Q,dx,dy,k,l;
int stx,sty,drx,dry;
int P1,P2;
char rez;
int main()
{
    fscanf(f,"%d %d %d\n",&N,&M,&Q);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
            D[i][j]=fgetc(f);
        fgetc(f);
    }
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            {D[i][j]=('1'-D[i][j])*(min(min(D[i-1][j-1],D[i-1][j]),D[i][j-1])+1);dp[0][0][i][j]=D[i][j];}
    for(i=N;i;i--)
    {
        for(j=M;j;j--)
        {
            for(k=0;i+(1<<k)-1<=N;k++)
            {
                for(l=0;j+(1<<l)-1<=M;l++)
                {
                    if(k!=0||l!=0)
                    {
                        if(k!=0)
                            dp[k][l][i][j]=max(dp[k-1][l][i][j],dp[k-1][l][i+(1<<(k-1))][j]);
                        else
                            dp[k][l][i][j]=max(dp[k][l-1][i][j],dp[k][l-1][i][j+(1<<(l-1))]);
                    }
                }
            }
        }
    }
    while(Q)
    {
        fscanf(f,"%d%d%d%d",&stx,&sty,&drx,&dry);
        dx=drx-stx;
        dy=dry-sty;
        P1=P2=1;
        while((1<<P1)<=dx)
            P1++;
        P1--;
        while((1<<P2)<=dy)
            P2++;
        P2--;
        rez=max(max(dp[P1][P2][stx][sty],dp[P1][P2][stx][dry-(1<<P2)+1]),max(dp[P1][P2][drx-(1<<P1)+1][sty],dp[P1][P2][drx-(1<<P1)+1][dry-(1<<P2)+1]));
        fprintf(g,"%d\n",(int)rez);
        Q--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
