#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
FILE *f=fopen("colaj.in","r");
FILE *g=fopen("colaj.out","w");
short N,M,nr;
struct{short X,Y,XX,YY;} A[105];
vector<short> VX,VY;
short V[205][205];
const short dx[]={-1,0,1,0};
const short dy[]={0,1,0,-1};
unordered_map<short,short> IX,IY;
void fi(short x,short y)
{
    V[x][y]=1;
    for(short k=0;k<4;k++)
    {
        if(x+dx[k]>=0&&x+dx[k]<=N&&y+dy[k]>=0&&y+dy[k]<=M&&!V[x+dx[k]][y+dy[k]])
        {
            fi(x+dx[k],y+dy[k]);
        }
    }
}
int main()
{
    fscanf(f,"%hd",&nr);
    fscanf(f,"%hd%hd",&N,&M);
    for(short i=1;i<=nr;i++)
    {
        fscanf(f,"%hd%hd%hd%hd",&A[i].X,&A[i].Y,&A[i].XX,&A[i].YY);
        VX.push_back(A[i].X);
        VX.push_back(A[i].XX);
        VY.push_back(A[i].Y);
        VY.push_back(A[i].YY);
    }
    VX.push_back(N);
    VX.push_back(0);
    VY.push_back(M);
    VY.push_back(0);
    sort(VX.begin(),VX.end());
    sort(VY.begin(),VY.end());
    N=VX.size()-1;M=VY.size()-1;
    short tmp=0;
    for(short i=0;i<=N;i++)
    {
        while(i<N&&VX[i]==VX[i+1]) i++;
        IX[VX[i]]=tmp,tmp++;
    }
    tmp=0;
    for(short i=0;i<=M;i++)
    {
        while(i<M&&VY[i]==VY[i+1]) i++;
        IY[VY[i]]=tmp,tmp++;
    }
    for(short i=1;i<=nr;i++)
    {
        V[IX[A[i].X]][IY[A[i].Y]]++;
        V[IX[A[i].XX]][IY[A[i].Y]]--;
        V[IX[A[i].X]][IY[A[i].YY]]--;
        V[IX[A[i].XX]][IY[A[i].YY]]++;
    }
    N=IX.size()-1;
    M=IY.size()-1;
    for(short i=1;i<=N;i++) V[i][0]+=V[i-1][0];
    for(short i=1;i<=M;i++) V[0][i]+=V[0][i-1];
    for(short i=1;i<=N;i++)
    {
        for(short j=1;j<=M;j++)
        {
            V[i][j]+=V[i-1][j]+V[i][j-1]-V[i-1][j-1];
        }
    }
    nr=0;N--;M--;
    for(short i=0;i<=N;i++)
    {
        for(short j=0;j<=M;j++)
        {
            if(!V[i][j])
            {
                fi(i,j);
                nr++;
            }
        }
    }
    fprintf(g,"%hd",nr);
    fclose(f);
    fclose(g);
    return 0;
}
