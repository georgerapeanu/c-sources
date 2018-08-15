#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>
#define ok(x,y) (0<x&&x<=N&&0<y&&y<=M&&V[x][y]!='#')
using namespace std;
FILE *f=fopen("miting.in","r");
FILE *g=fopen("miting.out","w");
short dp[11][11][61][61];
int N,M,T,K;
queue<int> Qx,Qy;
char V[62][65];
char cuv[15];
unordered_map<char,int> poz;
pair<int,int> unde[11];
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
void update(int i,int j)///presupui ca in zonele x,y se intalnesc pentru prima data si cu Lee updatezi daca e nevoie celelalte pozitii
{
    while(!Qx.empty())
    {
        int x1,y1;
        x1=Qx.front(),Qx.pop();
        y1=Qy.front(),Qy.pop();
        for(int k=0;k<4;k++)
        {
            int x2=x1+dx[k],y2=y1+dy[k];
            if(ok(x2,y2)&&dp[i][j][x1][y1]+1<dp[i][j][x2][y2])
                dp[i][j][x2][y2]=dp[i][j][x1][y1]+1,Qx.push(x2),Qy.push(y2);
        }
    }
}
int main()
{
    fscanf(f,"%d\n%d %d\n",&T,&N,&M);
    fgets(cuv+1,15,f);
    K=strlen(cuv+1);K-=(cuv[K]=='\n');
    int stx=N,sty=M,drx=0,dry=0;
    for(int i=1;i<=K;i++) poz[cuv[i]]=i;
    for(int i=1;i<=N;i++)
    {
        fgets(V[i]+1,65,f);
        for(int j=1;j<=M;j++)
            if(V[i][j]!='#'&&V[i][j]!='_')
                {unde[poz[V[i][j]]]=make_pair(i,j);stx=min(i,stx);drx=max(i,drx);sty=min(j,sty);dry=max(j,dry);}
    }
    if(T==1)
    {
        fprintf(g,"%d",(drx-stx+1)*(dry-sty+1));return 0;
    }
    for(int i=1;i<=K;dp[i][i][unde[i].first][unde[i].second]=0,Qx.push(unde[i].first),Qy.push(unde[i].second),update(i,i),i++)
        for(int j=i;j<=K;j++)
            for(int k=1;k<=N;k++)
                for(int l=1;l<=M;l++)
                    dp[i][j][k][l]=(1<<13);
    for(int l=2;l<=K;l++)
    {
        for(int i=1;i<=K-l+1;i++)
        {
            int j=i+l-1;
            for(int x1=1;x1<=N;x1++)
            {
                for(int y1=1;y1<=M;y1++)
                {
                    short vmin=dp[i][j][x1][y1];
                    for(int k=i;k<j;k++)
                    {
                        vmin=min(1*vmin,dp[i][k][x1][y1]+dp[k+1][j][x1][y1]);
                    }
                    if(vmin<dp[i][j][x1][y1])
                    {
                        dp[i][j][x1][y1]=vmin;
                        Qx.push(x1);
                        Qy.push(y1);
                    }
                }
            }
            update(i,j);
        }
    }
    short vmin=(1<<13);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            vmin=min(dp[1][K][i][j],vmin);
    if(vmin==(1<<13))
        fprintf(g,"-1");
    else
        fprintf(g,"%hd",vmin);
    fclose(f);
    fclose(g);
    return 0;
}
