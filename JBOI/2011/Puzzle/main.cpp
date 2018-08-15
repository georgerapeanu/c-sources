#include <iostream>
#include <cstdlib>
using namespace std;
int M[5][25][25];
int rez[50][50];
int N;
int ord[5];
bool used[5];
int nr;
void eval()
{
    nr++;
    for(int i=1;i<2*N;i++)for(int j=1;j<2*N;j++)rez[i][j]=0;
    for(int i=1;i<=4;i++)
    {
        int ind=ord[i];
        int x,y,xx,yy;
        if(i==1)     {x=y=1;xx=yy=N;}
        else if(i==2){x=1;y=N;xx=N;yy=2*N-1;}
        else if(i==3){x=N;y=1;xx=2*N-1;yy=N;}
        else         {x=y=N;xx=yy=2*N-1;}
        for(int j=x;j<=xx;j++)
            for(int k=y;k<=yy;k++)
            {
                if(rez[j][k]!=0&&M[ind][j-x+1][k-y+1]!=0)return ;
                if(M[ind][j-x+1][k-y+1]!=0)rez[j][k]=M[ind][j-x+1][k-y+1];
            }
    }
    for(int i=1;i<2*N;i++,cout<<"\n")
        for(int j=1;j<2*N;j++)cout<<rez[i][j]<<" ";
    exit(0);
}
void rot(int mat[][25])
{
    int tmp[25][25];
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            tmp[N-j+1][i]=mat[i][j];
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)mat[i][j]=tmp[i][j];
}
void flip(int mat[][25])
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;2*j<=N;j++)
            swap(mat[i][j],mat[i][N-j+1]);
    }
}
void btr(int pas)
{
    if(pas>4){eval();return;}
    for(int i=1;i<=4;i++)
    {
        if(!used[i])
        {
            used[i]=1;
            ord[pas]=i;
            for(int j=1;j<=4;j++)
            {
                btr(pas+1);
                rot(M[i]);
            }
            flip(M[i]);
            for(int j=1;j<=4;j++)
            {
                btr(pas+1);
                rot(M[i]);
            }
            flip(M[i]);
            used[i]=0;
        }
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=N;j++)
            for(int k=1;k<=N;k++)
                cin>>M[i][j][k];
    btr(1);
    return 0;
}
