#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("dreptunghiuri2.in","r");
FILE *g=fopen("dreptunghiuri2.out","w");
int N,M,D,O,nr;
bool V[1005][1005];
int i,j;
int S[1005][1005];
struct {int x,y;} dr;
queue <int> Qx,Qy;
const int dirx[]={-1,0,1,0,-1,-1,1,1};
const int diry[]={0,1,0,-1,-1,1,1,-1};
void filul()
{
    dr={i,j};
    V[i][j]=0;
    Qx.push(i);
    Qy.push(j);
    while(!Qx.empty())
    {
        int x,y;
        x=Qx.front();
        y=Qy.front();
        dr={max(dr.x,x),max(dr.y,y)};
        Qx.pop();
        Qy.pop();
        for(int i=0;i<4;i++)
        {
            if(V[x+dirx[i]][y+diry[i]]==1)
            {
                Qx.push(x+dirx[i]);
                Qy.push(y+diry[i]);
                V[x+dirx[i]][y+diry[i]]=0;
            }
        }
    }
}
void Fillu()
{
    dr={i,j};
    int cul=S[i][j];
    S[i][j]=0;
    Qx.push(i);
    Qy.push(j);
    while(!Qx.empty())
    {
        int x,y;
        x=Qx.front();
        y=Qy.front();
        dr={max(dr.x,x),max(dr.y,y)};
        Qx.pop();
        Qy.pop();
        for(int i=0;i<8;i++)
        {
            if(S[x+dirx[i]][y+diry[i]]==cul)
            {
                 Qx.push(x+dirx[i]);
                Qy.push(y+diry[i]);
                S[x+dirx[i]][y+diry[i]]=0;
            }
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
            fscanf(f,"%d",&V[i][j]);
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(V[i][j])
            {
                filul();
                D++;
                S[i][j]=S[dr.x+1][dr.y+1]=1;
                S[i][dr.y+1]=-1;
                S[dr.x+1][j]=-1;
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
            S[i][j]=S[i][j-1]+S[i-1][j]-S[i-1][j-1]+S[i][j];
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(S[i][j]!=0)
            {
                if(O<S[i][j])
                {
                    O=S[i][j];
                    nr=1;
                }
                else if(O==S[i][j])
                    nr++;
                Fillu();
            }
        }
    }
    fprintf(g,"%d %d %d",D,O,nr);
    fclose(f);
    fclose(g);
    return 0;
}
