#include <cstdio>
#include <queue>
#include <set>
using namespace std;
FILE *f=fopen("ferma1.in","r");
FILE *g=fopen("ferma1.out","w");
int P,N,M;
char C[405][405];
int V[405][405];
int val[160005],i,j,k,maxim;
char cul[160005];
typedef struct{int x,y;} point;
queue <point> Q;
set <int> tmp;
set <int> used;
point a;
const int dirx[]={-1,0,1,0};
const int diry[]={0,1,0,-1};
char rezc;
int l,c;
int main()
{
    fscanf(f,"%d",&P);
    fscanf(f,"%d %d\n",&N,&M);
    for(i=1;i<=N;i++)
    {
        fgets(C[i]+1,405,f);
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(!V[i][j])
            {
                Q.push({i,j});
                V[i][j]=++V[0][0];
                val[V[0][0]]=1;
                cul[V[0][0]]=C[i][j];
                while(!Q.empty())
                {
                    a=Q.front();
                    Q.pop();
                    for(k=0;k<4;k++)
                    {
                        if(C[a.x+dirx[k]][a.y+diry[k]]==C[a.x][a.y]&&!V[a.x+dirx[k]][a.y+diry[k]])
                        {
                            val[V[a.x][a.y]]++;
                            Q.push({a.x+dirx[k],a.y+diry[k]});
                            V[a.x+dirx[k]][a.y+diry[k]]=V[a.x][a.y];
                        }
                    }
                }
                if(val[V[0][0]]>maxim)
                    maxim=val[V[0][0]];
            }
        }
    }
    if(P==1)
    {
        fprintf(g,"%d",maxim);
        return 0;
    }
    maxim =0;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            tmp.insert(V[i-1][j]);
            tmp.insert(V[i+1][j]);
            tmp.insert(V[i][j+1]);
            tmp.insert(V[i][j-1]);
            int tmprez=0;
            for(set <int> ::iterator it=tmp.begin();it!=tmp.end();it++)
            {
                tmprez=val[*it];
                used.insert(*it);
                if(cul[*it]!=C[i][j])
                    tmprez++;
                for(k=0;k<4;k++)
                {
                    if(C[i+dirx[k]][j+diry[k]]==cul[*it]&&used.find(V[i+dirx[k]][j+diry[k]])==used.end())
                        {tmprez+=val[V[i+dirx[k]][j+diry[k]]];used.insert(V[i+dirx[k]][j+diry[k]]);}
                }
                if(tmprez>maxim)
                        {maxim=tmprez;rezc=cul[*it];l=i;c=j;}
                used.clear();
            }
            tmp.clear();
        }
    }
    fprintf(g,"%d %d\n%c",l,c,rezc);
    return 0;
}
