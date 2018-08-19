#include <cstdio>
#include <algorithm>
#define MOD 1000000007
using namespace std;
int dp[1005][1005];
int U[1005][1005];
int D[1005][1005];
char C[1005][1005];
int N,M,R1,R2;
int nr[280];
int nrU[1005][1005];
int nrD[1005][1005];
bool only=1;
long long rez=0;
bool u[1005][1005];
int add(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
}
int scad(int a,int b)
{
    a-=b;
    if(a<0)a+=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
void btr(int x,int y)
{
    if(x==R2&&y==M)
    {
        u[x][y]=1;
        int tmp=1;
        for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)if(!u[i][j])tmp=mult(tmp,nr[C[i][j]]);
        rez=add(rez,tmp);
        u[x][y]=0;
        return;
    }
    //u[x][y]=1;
    if(C[x-1][y]=='0'&&!u[x-1][y]){btr(x-1,y);u[x][y]=0;return ;}
    else if(C[x-1][y]=='?'&&!u[x-1][y])
    {
        btr(x-1,y);
    }
    u[x-1][y]=1;
    if(C[x][y+1]=='0'){btr(x+1,y);u[x][y]=u[x-1][y]=0;return ;}
    else if(C[x][y+1]=='?')btr(x,y+1);
   // u[x][y+1]=1;
    if(C[x+1][y]=='0'&&!u[x+1][y]){btr(x+1,y);u[x][y]=u[x-1][y]=u[x][y+1]=0;return ;}
    else if(C[x+1][y]=='?'&&!u[x+1][y])btr(x+1,y);
    u[x][y]=u[x-1][y]=u[x][y+1]=0;
}
int main() {
    scanf("%d %d %d %d\n",&N,&M,&R1,&R2);
    nr['0']=nr['1']=1;
    nr['?']=2;
    for(int i=1;i<=N;i++)fgets(C[i]+1,1005,stdin);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(C[i][j]=='?')only=0;
        }
    }
    if(only)
    {
        int x=R1,y=1;
        while(1)
        {
            if(x==R2&&y==M)
            {
                printf("1");return 0;
            }
            else if(C[x-1][y]=='0')x--;
            else if(C[x][y+1]=='0')y++;
            else if(C[x+1][y]=='0')x++;
            else {printf("0");return 0;}
        }
    }
    if(C[R1][1]=='1'||C[R2][M]=='1')printf("0");
    else
    {
        btr(R1,1);
        printf("%d",rez);
    }
    return 0;
}
