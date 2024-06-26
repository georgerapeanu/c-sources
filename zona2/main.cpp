#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
FILE *f=fopen("zona2.in","r");
FILE *g=fopen("zona2.out","w");
int M[55][55],A;
queue <pair<int,int>> Q;
int X,Y,N,L,i,ctr,dir,pasi;
const int dirX[]={0,-1,0,1,0};
const int dirY[]={0,0,1,0,-1};
int main()
{
    fscanf(f,"%d %d %d %d",&X,&Y,&N,&L);
    X++;
    Y++;
    M[X][Y]=1;
    for(i=1;i<=L&&pasi==0;i++)
    {
        fscanf(f,"%d",&dir);
        X+=dirX[dir];
        Y+=dirY[dir];
        if(M[X][Y])
            pasi=M[X-dirX[dir]][Y-dirY[dir]]-M[X][Y]+1;
        else
            M[X][Y]=M[X-dirX[dir]][Y-dirY[dir]]+1;
    }
    fprintf(g,"%d\n",pasi);
    Q.push(make_pair(0,0));
    M[0][0]=1;
    while(!Q.empty())
    {
        X=(Q.front()).first;
        Y=(Q.front()).second;
        A++;
        Q.pop();
        for(i=1;i<=4;i++)
             if(X+dirX[i]>=0&&X+dirX[i]<=N&&Y+dirY[i]>=0&&Y+dirY[i]<=N&&M[X+dirX[i]][Y+dirY[i]]==0)
                {M[X+dirX[i]][Y+dirY[i]]=1;Q.push(make_pair(X+dirX[i],Y+dirY[i]));}
    }
    A=(N+1)*(N+1)-A;
    fprintf(g,"%d",(A-(pasi+2)/2));
    fclose(f);
    fclose(g);
    return 0;
}
