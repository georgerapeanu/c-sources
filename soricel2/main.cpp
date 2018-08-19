#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
FILE *f=fopen("soricel2.in","r");
FILE *g=fopen("soricel2.out","w");
int N,M;
int S[105][105];
int P[105][105];
int i,j,AL,OL;
typedef struct {int x,y;} POINT;
POINT s,p,A[505],a,b,c,d,rez[505];
const int dx[]={-1,-1,0,1,1,1,0,-1};
const int dy[]={0,1,1,1,0,-1,-1,-1};
queue <POINT> Q;
bool cmp(POINT A,POINT B)
{
    if(A.x!=B.x)
        return A.x<B.x;
    return A.y<B.y;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    fscanf(f,"%d %d",&s.x,&s.y);
    fscanf(f,"%d %d",&p.x,&p.y);
    fscanf(f,"%d",&AL);
    for(i=1;i<=AL;i++)
        fscanf(f,"%d %d",&A[i].x,&A[i].y);
    sort(A+1,A+1+AL,cmp);
    fscanf(f,"%d",&OL);
    while(OL--)
    {
        fscanf(f,"%d %d",&a.x,&a.y);
        S[a.x][a.y]=P[a.x][a.y]=-1;
    }
    for(i=0;i<=N+1;i++)
        S[i][0]=S[i][M+1]=P[i][0]=P[i][M+1]=-1;
    for(i=0;i<=M+1;i++)
        S[0][i]=S[N+1][i]=P[0][i]=P[N+1][i]=-1;
    S[s.x][s.y]=1;
    Q.push(s);
    while(!Q.empty())
    {
        a=Q.front();
        Q.pop();
        for(i=0;i<8;i++)
        {
            b.x=a.x+dx[i];
            b.y=a.y+dy[i];
            if(S[b.x][b.y]==0)
            {S[b.x][b.y]=S[a.x][a.y]+1;Q.push(b);}
        }
    }
    P[p.x][p.y]=1;
    Q.push(p);
    while(!Q.empty())
    {
        a=Q.front();
        Q.pop();
        for(i=0;i<8;i++)
        {
            b.x=a.x+dx[i];
            b.y=a.y+dy[i];
            if(P[b.x][b.y]==0)
            {P[b.x][b.y]=P[a.x][a.y]+1;Q.push(b);}
        }
    }
    OL=0;
    for(i=1;i<=AL;i++)
    {
        if(S[A[i].x][A[i].y]&&S[A[i].x][A[i].y]-1<(P[A[i].x][A[i].y]-1)/2+1-P[A[i].x][A[i].y]%2)
            rez[++OL]=A[i];
    }
    fprintf(g,"%d\n",OL);
    for(i=1;i<=OL;i++)
        fprintf(g,"%d %d\n",rez[i].x,rez[i].y);
    fclose(f);
    fclose(g);
    return 0;
}
