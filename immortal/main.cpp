#include <cstdio>
#include <cstdlib>
#include <fstream>
#define x first
#define x1 first.first
#define x2 second.first
#define y second
#define y1 first.second
#define y2 second.second
using namespace std;
FILE *f=fopen("immortal.in","r");
FILE *g=fopen("immortal.out","w");
pair<pair<int,int>,pair<int,int> > V[20];
pair<int,int> A[25];
int N,M,I;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int B[25][25];
void btr(int pas)
{
    if(pas>=I)
    {
        for(int i=1;i<I;i++)
            fprintf(g,"%d %d %d %d\n",V[i].x1,V[i].y1,V[i].x2,V[i].y2);
        exit(0);
    }
    for(int i=1;i<=I;i++)
    {
        if(B[A[i].x][A[i].y]==i)
        {
            for(int k=0;k<4;k++)
            {
                if(B[A[i].x+dx[k]][A[i].y+dy[k]]>0&&B[A[i].x+2*dx[k]][A[i].y+2*dy[k]]==0)
                {
                    int tmp=B[A[i].x+dx[k]][A[i].y+dy[k]];
                    B[A[i].x][A[i].y]=0;
                    B[A[i].x+dx[k]][A[i].y+dy[k]]=0;
                    B[A[i].x+2*dx[k]][A[i].y+2*dy[k]]=i;
                    A[i].x+=2*dx[k];A[i].y+=2*dy[k];
                    V[pas]=make_pair(make_pair(A[i].x-2*dx[k],A[i].y-2*dy[k]),make_pair(A[i].x,A[i].y));
                    btr(pas+1);
                    A[i].x-=2*dx[k];A[i].y-=2*dy[k];
                    B[A[i].x+2*dx[k]][A[i].y+2*dy[k]]=0;
                    B[A[i].x+dx[k]][A[i].y+dy[k]]=tmp;
                    B[A[i].x][A[i].y]=i;
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&I);
    for(int i=1;i<=I;i++)
    {
        fscanf(f,"%d%d",&A[i].x,&A[i].y);
        B[A[i].x][A[i].y]=i;
    }
    for(int i=0;i<=N+1;i++) B[i][0]=B[i][M+1]=-1;
    for(int i=0;i<=M+1;i++) B[0][i]=B[N+1][i]=-1;
    btr(1);
    fclose(f);
    fclose(g);
    return 0;
}
