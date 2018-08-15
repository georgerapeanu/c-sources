#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int L[205];
int C[205];
int N;
bool viz[205][205];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int V[205][205];
int model5[][5]={1,2,0,0,3,
3,0,1,2,0,
2,0,0,3,1,
0,3,2,1,0,
0,1,3,0,2
};
int model6[][6]={1,2,3,0,0,0,
3,0,1,0,2,0,
0,0,0,2,3,1,
0,1,0,3,0,2,
0,3,2,1,0,0,
2,0,0,0,1,3
};
int model7[][7]=
{1,2,3,0,0,0,0,
3,0,1,0,0,2,0,
0,0,0,2,3,0,1,
0,0,0,0,1,3,2,
0,1,0,3,2,0,0,
0,3,2,1,0,0,0,
2,0,0,0,0,1,3
};
int model8[][8]={1,2,3,0,0,0,0,0,
3,0,1,0,0,0,2,0,
0,0,0,0,2,3,0,1,
0,0,0,3,0,1,0,2,
0,1,0,0,0,2,3,0,
0,0,2,1,3,0,0,0,
0,3,0,2,1,0,0,0,
2,0,0,0,0,0,1,3
};
int model9[][9]={1,2,3,0,0,0,0,0,0,
3,0,1,0,0,0,0,2,0,
0,0,0,0,0,0,2,3,1,
0,0,0,0,3,1,0,0,2,
0,1,0,3,0,2,0,0,0,
0,0,0,2,1,3,0,0,0,
0,0,2,1,0,0,3,0,0,
0,3,0,0,2,0,1,0,0,
2,0,0,0,0,0,0,1,3
};
int model10[][10]={1,2,3,0,0,0,0,0,0,0,
3,0,1,0,0,0,0,0,2,0,
0,0,0,0,0,0,0,2,3,1,
0,0,0,0,3,1,0,0,0,2,
0,0,0,1,2,3,0,0,0,0,
0,1,0,3,0,0,2,0,0,0,
0,0,0,2,1,0,3,0,0,0,
0,0,2,0,0,0,1,3,0,0,
0,3,0,0,0,2,0,1,0,0,
2,0,0,0,0,0,0,0,1,3
};

bool eval()
{
    for(int i=1;i<=N;i++)
    {
        if(L[i]!=7||C[i]!=7)return 0;
    }
    return 1;
}
bool btr(int x,int y,int dir,int val,bool change)
{
    bool rez=0;
    if(change)
    {
        if((dir==1||dir==3)&&C[y-dy[dir]]!=7)return 0;
        if((dir==2||dir==0)&&L[x-dx[dir]]!=7)return 0;
    }
    if(viz[x+dx[dir]][y+dy[dir]]&&viz[x+dx[(dir+1)%4]][y+dy[(dir+1)%4]])
    {
        if(eval())
        {
            cout<<"{";
            for(int i=1;i<=N;i++)
            {
                for(int j=1;j<=N;j++)
                {
                    cout<<V[i][j]<<(i==N&&j==N ? "":",");
                }
                cout<<"\n";
            }
            //cout<<"\n\n\n";
            cout<<"}";
            return 1;
        }
        return 0;
    }
    if(viz[x+dx[dir]][y+dy[dir]])
    {
        dir=(dir+1)%4;
        change=1;
    }
    else
    {
        change=0;
    }
    viz[x][y]=1;
    if((L[x]&(1<<(val-1)))==0&&(C[y]&(1<<(val-1)))==0)//&&(((x<=3&&y<=3)||(x<=3&&y>=N-2)||(x>=N-2&&y<=3)||(x>=N-2&&y>=N-2))||(x>3&&y>3&&x<N-2&&y<N-2))
    {
        L[x]^=(1<<(val-1));
        C[y]^=(1<<(val-1));
        V[x][y]=val;
        rez=btr(x+dx[dir],y+dy[dir],dir,val%3+1,change);
        L[x]^=(1<<(val-1));
        C[y]^=(1<<(val-1));
    }
    V[x][y]=0;
    if(!rez)
        rez=btr(x+dx[dir],y+dy[dir],dir,val,change);
    viz[x][y]=0;
    return rez;
}
void fa(int i)
{
    N=i;
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)viz[i][j]=0;
    for(int i=0;i<=N+1;i++)viz[0][i]=viz[N+1][i]=viz[i][0]=viz[i][N+1]=1;
    btr(1,1,1,1,0);
    cout<<"\n\n\n";
}
void smecheriisecreteaicia()
{
    freopen("out","w",stdout);
    for(int i=5;i<=11;i++)fa(i);
}
void solve(int N,int x1,int y1,int x2,int y2)
{
    if(N<11)
    {
        for(int i=x1;i<=x2;i++)
        {
            for(int j=y1;j<=y2;j++)
            {
                if(N==5)V[i][j]=model5[i-x1][j-y1];
                else if(N==6)V[i][j]=model6[i-x1][j-y1];
                else if(N==7)V[i][j]=model7[i-x1][j-y1];
                else if(N==8)V[i][j]=model8[i-x1][j-y1];
                else if(N==9)V[i][j]=model9[i-x1][j-y1];
                else if(N==10)V[i][j]=model10[i-x1][j-y1];
            }
        }
        return ;
    }
    for(int i=x1;i<x1+3;i++)
        for(int j=y1;j<y1+3;j++)
            V[i][j]=model6[i-x1][j-y1];
    for(int i=x1;i<x1+3;i++)
        for(int j=y2;j>y2-3;j--)
            V[i][j]=model6[i-x1][5-y2+j];
    for(int i=x2;i>x2-3;i--)
        for(int j=y1;j<y1+3;j++)
            V[i][j]=model6[5-x2+i][j-y1];
    for(int i=x2;i>x2-3;i--)
        for(int j=y2;j>y2-3;j--)
            V[i][j]=model6[5-x2+i][5-y2+j];
    solve(N-6,x1+3,y1+3,x2-3,y2-3);
}
int main()
{
    cin>>N;
    solve(N,1,1,N,N);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            cout<<V[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
