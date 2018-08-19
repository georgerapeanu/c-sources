#include <cstdio>
#include <vector>
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;
FILE *f=fopen("obmax.in","r");
FILE *g=fopen("obmax.out","w");
const int dx[]={-1,-1,0,1,1,1,0,-1};
const int dy[]={0,1,1,1,0,-1,-1,-1};
vector<pair<int,int> > tmp,V;
bool B[20][20];
int X,Y,rx,ry;
int N,M;
short A[20][20];
void fi(int x,int y)
{
    B[x][y]=1;
    tmp.pb(mp(x-X,y-Y));
    for(int k=0;k<8;k++)
        if(!B[x+dx[k]][y+dy[k]])
            fi(x+dx[k],y+dy[k]);
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            {fscanf(f,"%hd",&A[i][j]);if(A[i][j]!=1) B[i][j]=1;}
    for(int i=0;i<=M+1;i++) A[0][i]=A[N+1][i]=B[0][i]=B[N+1][i]=1;
    for(int i=0;i<=N+1;i++) A[i][0]=A[i][M+1]=B[i][0]=B[i][M+1]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(!B[i][j])
            {
                X=i;
                Y=j;
                tmp.clear();
                fi(i,j);
                if(tmp.size()>V.size())
                {
                    rx=i;ry=j;
                    V.clear();
                    V.assign(tmp.begin(),tmp.end());
                }
            }
        }
    }
    for(auto it:V)
        A[rx+it.x][ry+it.y]=2;
    bool gasit=0;
    for(int i=1;i<=N&&(!gasit);i++)
    {
        for(int j=1;j<=M&&(!gasit);j++)
        {
            bool ok=1;
            for(auto it:V)
            {
                if(A[i+it.x][j+it.y]!=0)
                    {ok=0;break;}
            }
            if(ok)
            {
                gasit=1;
                for(auto it:V)
                    A[i+it.x][j+it.y]=3;
            }
        }
    }
    for(int i=1;i<=N;i++,fprintf(g,"\n"))
        for(int j=1;j<=M;j++)
            fprintf(g,"%hd ",A[i][j]);
    fclose(f);
    fclose(g);
    return 0;
}
