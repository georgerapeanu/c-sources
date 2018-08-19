#include <cstdio>
#include<queue>
#define inf 999999999
using namespace std;
FILE *f=fopen("vis.in","r");
FILE *g=fopen("vis.out","w");
typedef struct{int x,y;} punct;
queue <punct> Q;
int N,K1,K2,L1,C1,L2,C2,dist1N,dist1A,dist1B,distAB,distAN,distBN,distBA,M[1005][1005],A[1005][1005],i,j,x,y,distBNcuA,distANcuB;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
int main()
{
    fscanf(f,"%d %d %d %d %d %d %d",&N,&K1,&K2,&L1,&C1,&L2,&C2);
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            fscanf(f,"%d",&M[i][j]);
    ///dist 1N,dist1B,dist1A
    Q.push({1,1});
    A[1][1]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        for(i=0;i<4;i++)
        {
            if(x+dirx[i]<=N&&x+dirx[i]>0&&y+diry[i]<=N&&y+diry[i]>0&&!A[x+dirx[i]][y+diry[i]]&&M[x+dirx[i]][y+diry[i]]==0)
            {
                A[x+dirx[i]][y+diry[i]]=A[x][y]+1;
                Q.push({x+dirx[i],y+diry[i]});
            }
        }
    }
    dist1A=A[L1][C1];if(dist1A==0) dist1A=inf;
    dist1B=A[L2][C2];if(dist1B==0) dist1B=inf;
    dist1N=A[N][N];if(dist1N==0) dist1N=inf;
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            A[i][j]=0;
    ///distAB,distAN
        Q.push({L1,C1});
    A[L1][C1]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        for(i=0;i<4;i++)
        {
            if(x+dirx[i]<=N&&x+dirx[i]>0&&y+diry[i]<=N&&y+diry[i]>0&&!A[x+dirx[i]][y+diry[i]]&&(M[x+dirx[i]][y+diry[i]]==0||M[x+dirx[i]][y+diry[i]]<=K1))
            {
                A[x+dirx[i]][y+diry[i]]=A[x][y]+1;
                Q.push({x+dirx[i],y+diry[i]});
            }
        }
    }
    distAB=A[L2][C2];if(distAB==0) distAB=inf;
    distAN=A[N][N];if(distAN==0) distAN=inf;
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            A[i][j]=0;
    ///distBN,distBA
        Q.push({L2,C2});
    A[L2][C2]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        for(i=0;i<4;i++)
        {
            if(x+dirx[i]<=N&&x+dirx[i]>0&&y+diry[i]<=N&&y+diry[i]>0&&!A[x+dirx[i]][y+diry[i]]&&(M[x+dirx[i]][y+diry[i]]==0||M[x+dirx[i]][y+diry[i]]>=K2))
            {
                A[x+dirx[i]][y+diry[i]]=A[x][y]+1;
                Q.push({x+dirx[i],y+diry[i]});
            }
        }
    }
    distBA=A[L1][C1];if(distBA==0) distBA=inf;
    distBN=A[N][N];if(distBN==0) distBN=inf;
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            A[i][j]=0;
    ///distBNcuA
            Q.push({L2,C2});
    A[L2][C2]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        for(i=0;i<4;i++)
        {
            if(x+dirx[i]<=N&&x+dirx[i]>0&&y+diry[i]<=N&&y+diry[i]>0&&!A[x+dirx[i]][y+diry[i]]&&(M[x+dirx[i]][y+diry[i]]==0||M[x+dirx[i]][y+diry[i]]<=K1||M[x+dirx[i]][y+diry[i]]>=K2))
            {
                A[x+dirx[i]][y+diry[i]]=A[x][y]+1;
                Q.push({x+dirx[i],y+diry[i]});
            }
        }
    }
    distBNcuA=A[N][N];if(distBNcuA==0) distBNcuA=inf;
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            A[i][j]=0;
    ///distANcuB
              Q.push({L1,C1});
    A[L1][C1]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        for(i=0;i<4;i++)
        {
            if(x+dirx[i]<=N&&x+dirx[i]>0&&y+diry[i]<=N&&y+diry[i]>0&&!A[x+dirx[i]][y+diry[i]]&&(M[x+dirx[i]][y+diry[i]]==0||M[x+dirx[i]][y+diry[i]]<=K1||M[x+dirx[i]][y+diry[i]]>=K2))
            {
                A[x+dirx[i]][y+diry[i]]=A[x][y]+1;
                Q.push({x+dirx[i],y+diry[i]});
            }
        }
    }
    distANcuB=A[N][N];if(distANcuB==0) distANcuB=inf;
    fprintf(g,"%d",min(dist1N,min(min(dist1A+distAN-1,dist1B+distBN-1),min(dist1A+distAB+distBNcuA-2,dist1B+distBA+distANcuB-2))));
    fclose(f);
    fclose(g);
    return 0;
}
//direct 1N
//1A+AN
//1B+BN
//1A+AB+BNcuA
//1B+BA+ANcuB

