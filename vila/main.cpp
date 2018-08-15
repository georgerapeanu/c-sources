#include <bits/stdc++.h>
using namespace std;
FILE *f=fopen("vila.in","r");
FILE *g=fopen("vila.out","w");
queue <int> Qx,Qy;
const int dirx[]={-1,0,1,0};
const int diry[]={0,1,0,-1};
int N,i,j,M,nr,maxim,rez,x,y;
int V[130][130];
int dim[16900];
char c;
set<int> S;
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            c=fgetc(f);
            if(c=='1')
                V[i][j]=-1;
        }
        c=fgetc(f);
    }
    for(i=0;i<=N+1;i++)
        V[i][0]=V[i][M+1]=-1;
    for(i=0;i<=M+1;i++)
        V[0][i]=V[N+1][i]=-1;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(!V[i][j])
            {
                nr=0;
                rez++;
                V[i][j]=rez;
                Qx.push(i);
                Qy.push(j);
                while(!Qx.empty())
                {
                    nr++;
                    x=Qx.front();
                    y=Qy.front();
                    Qx.pop();
                    Qy.pop();
                    for(int k=0;k<4;k++)
                       if(!V[x+dirx[k]][y+diry[k]])
                        {
                            V[x+dirx[k]][y+diry[k]]=rez;
                            Qx.push(x+dirx[k]);
                            Qy.push(y+diry[k]);
                        }
                }
                if(maxim<nr)
                    maxim=nr;
                dim[rez]=nr;
            }
        }
    }
    fprintf(g,"%d\n%d\n",rez,maxim);
    maxim=0;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(V[i][j]==-1)
            {
                for(int k=0;k<4;k++)
                    S.insert( V[i+dirx[k]][j+diry[k]]);
                nr=1;
                for(auto it:S)
                {
                    if(it!=-1)
                    {
                        nr+=dim[it];
                    }
                }
                if(nr>maxim)
                {
                    maxim=nr;
                    x=i;
                    y=j;
                }
                S.clear();
            }
        }
    }
    fprintf(g,"%d %d %d",x,y,maxim);
    fclose(f);
    fclose(g);
    return 0;
}
