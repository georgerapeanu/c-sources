#include <cstdio>
using namespace std;
FILE *f=fopen("caibicol.in","r");
FILE *g=fopen("caibicol.out","w");
int dp[505][505][2];
int minim,i,j,k,l,N,K,tmp;
typedef struct {int x,y;} data;
data V[505];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&tmp);
        tmp==1 ? V[i].x++:V[i].y++;
        V[i]={V[i-1].x+V[i].x,V[i-1].y+V[i].y};
    }
    i=1;
    for(k=1;k<=K;k++)
    {
        if(k!=1)
        {
                for(j=1;j<=N;j++)
                {
                     minim=99999;
                    for(l=i;l<=j;l++)
                    {
                        if(minim>dp[i][l][(k+1)%2]+(V[j].x-V[l].x)*(V[j].y-V[l].y))
                            minim=dp[i][l][(k+1)%2]+(V[j].x-V[l].x)*(V[j].y-V[l].y);
                    }
                    dp[i][j][k%2]=minim;
                }
        }
        else
        {
                for(j=1;j<=N;j++)
                {
                    dp[i][j][1]=(V[j].x-V[i-1].x)*(V[j].y-V[i-1].y);
                }
        }
    }
    fprintf(g,"%d",dp[1][N][K%2]);
    return 0;
}
