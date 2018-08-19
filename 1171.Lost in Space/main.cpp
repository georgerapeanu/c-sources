#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#define X 5
#define NMAX 17
#define ZMAX 280
using namespace std;
int N;
int dniv[X][X][ZMAX];
unsigned int pre[17][X][X][ZMAX];
unsigned int ant[X][X][ZMAX];
int Z[17][X][X][ZMAX];
int V[17][X][X];
bool viz[X][X];
int nrz;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
unsigned int path;
bool usa[17][X][X];
int l,c,stx,sty;
int dim;
char R[ZMAX];
int dp[17][X][X][ZMAX];
char A[]={'N','E','S','W'};
bool ok(int x,int y)
{
    return (x>0&&x<X&&y>0&&y<X&&(!viz[x][y]));
}
void btr(int nivel,int drx,int dry,int nrz,int suma,int path)
{
    viz[drx][dry]=1;
    if(dniv[drx][dry][nrz]<suma)
    {
        dniv[drx][dry][nrz]=suma;
        ant[drx][dry][nrz]=path;
    }
    for(int k=0;k<4;k++)
    {
        int nx=drx+dx[k];
        int ny=dry+dy[k];
        if(ok(nx,ny))
            btr(nivel,nx,ny,nrz+1,suma+V[nivel][nx][ny],path*4+k);
    }
    viz[drx][dry]=0;
}
void fipath(int nvl,int ux,int uy)
{
    memset(dniv,0,sizeof(dniv));
    btr(nvl,ux,uy,1,V[nvl][ux][uy],0);
    for(int i=1;i<X;i++)
    {
        for(int j=1;j<X;j++)
        {
            for(int z1=1;z1<ZMAX-16;z1++)
            {
                for(int z2=1;z2<17;z2++)
                {
                    if(dp[nvl-1][ux][uy][z1]&&dniv[i][j][z2]&&dp[nvl][i][j][z1+z2]<dp[nvl-1][ux][uy][z1]+dniv[i][j][z2])
                    {
                        dp[nvl][i][j][z1+z2]=dp[nvl-1][ux][uy][z1]+dniv[i][j][z2];
                        pre[nvl][i][j][z1+z2]=ant[i][j][z2];
                        Z[nvl][i][j][z1+z2]=z2-1;
                    }
                }
            }
        }
    }
}
void sol(int nvl,int x,int y,int z)
{
    if(!nvl)
        return ;
    int nz=Z[nvl][x][y][z];
    int nx=x,ny=y,path=pre[nvl][x][y][z];
    while(nz)
    {
        R[++dim]=A[path%4];
        nx-=dx[path%4];
        ny-=dy[path%4];
        path/=4;
        nz--;
    }
    R[++dim]='D';
    sol(nvl-1,nx,ny,z-Z[nvl][x][y][z]-1);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<X;j++)
        {
            for(int k=1;k<X;k++)
            {
                cin>>V[i][j][k];
            }
        }
        for(int j=1;j<X;j++)
        {
            for(int k=1;k<X;k++)
            {
                cin>>usa[i][j][k];
            }
        }
    }
    cin>>l>>c;
    btr(1,l,c,1,V[1][l][c],0);
    for(int i=1;i<X;i++)
        for(int j=1;j<X;j++)
            for(int z=1;z<17;z++)
                dp[1][i][j][z]=dniv[i][j][z],Z[1][i][j][z]=z-1,pre[1][i][j][z]=ant[i][j][z];
    for(int nvl=2;nvl<=N;nvl++)
    {
        for(int X1=1;X1<X;X1++)
        {
            for(int Y1=1;Y1<X;Y1++)
            {
                if(usa[nvl-1][X1][Y1])
                {
                    fipath(nvl,X1,Y1);
                }
            }
        }
    }
    double rez=0;
    int xx,yy,zz;
    for(int i=1;i<X;i++)
        for(int j=1;j<X;j++)
            for(int z=1;z<ZMAX;z++)
                if(rez<dp[N][i][j][z]*1.0/z)
                    rez=dp[N][i][j][z]*1.0/z,xx=i,yy=j,zz=z;
    cout<<fixed<<setprecision(10)<<rez<<"\n";
    sol(N,xx,yy,zz);
    reverse(R+1,R+1+zz);
    cout<<dim-1<<"\n";
    cout<<R+2;
    return 0;
}
