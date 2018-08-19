#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
FILE *f=fopen("ternar.in","r");
FILE *g=fopen("ternar.out","w");
int N,M,V[1250][1250],i,j,arie,x,y,k,maxim;
typedef struct  {int x,y;} punct;
punct st,dr;
const int dirx[]={-1,0,1,0,-1,-1,1,1};
const int diry[]={0,1,0,-1,-1,1,1,-1};
void fil()
{
    queue <punct> Q;
    Q.push({i,j});
    arie=0;
    st=dr={i,j};
    V[i][j]=1;
    while(!Q.empty())
    {
        x=(Q.front()).x;
        y=(Q.front()).y;
        Q.pop();
        st={min(st.x,x),min(st.y,y)};
        dr={max(dr.x,x),max(dr.y,y)};
        arie++;
        for(k=0;k<8;k++)
        {
            if(V[x+dirx[k]][y+diry[k]]==0)
                {arie=0;return ;}
            else if(V[x+dirx[k]][y+diry[k]]==2)
            {
                V[x+dirx[k]][y+diry[k]]=1;
                Q.push({x+dirx[k],y+diry[k]});
            }
        }
    }
    return ;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&V[i][j]);
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(V[i][j]==2)
            {
                fil();
                if(arie==(dr.x-st.x+1)*(dr.y-st.y+1))
                {
                    maxim=max(arie+2*(dr.x-st.x+dr.y-st.y+2)+4,maxim);
                }
            }
        }
    }
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
