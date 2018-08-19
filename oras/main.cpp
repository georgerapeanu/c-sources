#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("oras1.in","r");
FILE *g=fopen("oras1.out","w");
int N,M,k,x,y;
char C[250][250];
int i,j,nr,p,c,P;
const int dirx[]={-1,0,1,0,-1,-1,1,1};
const int diry[]={0,1,0,-1,-1,1,1,-1};
queue <int> Qx,Qy;
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(i=1;i<=N;i++)
    {
        fgets(C[i]+1,250,f);
    }
    for(i=0;i<=N+1;i++)
        C[i][0]=C[i][M+1]='.';
    for(i=0;i<=M+1;i++)
        C[0][i]=C[N+1][i]='.';
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(C[i][j]!='.')
            {
                for(k=0;k<8;k++)
                {
                    if(C[i+dirx[k]][j+diry[k]]=='.')
                    {
                        nr++;
                        k=8;
                    }
                }
            }
        }
    }
    fprintf(g,"%d ",nr);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(C[i][j]=='P')
            {
                Qx.push(i);Qy.push(j);
                C[i][j]='.';
                p=0;
                while(!Qx.empty())
                {
                    x=Qx.front();
                    y=Qy.front();
                    Qx.pop();
                    Qy.pop();
                    p++;
                    for(k=0;k<4;k++)
                    {
                        if(C[x+dirx[k]][y+diry[k]]=='P')
                        {
                            C[x+dirx[k]][y+diry[k]]='.';
                            Qx.push(x+dirx[k]);
                            Qy.push(y+diry[k]);
                        }
                    }
                }
                if(p>P)
                    P=p;
            }
            else if(C[i][j]=='C')
            {
                Qx.push(i);Qy.push(j);
                C[i][j]='.';
                while(!Qx.empty())
                {
                    x=Qx.front();
                    y=Qy.front();
                    Qx.pop();
                    Qy.pop();
                    for(k=0;k<4;k++)
                    {
                        if(C[x+dirx[k]][y+diry[k]]=='C')
                        {
                            C[x+dirx[k]][y+diry[k]]='.';
                            Qx.push(x+dirx[k]);
                            Qy.push(y+diry[k]);
                        }
                    }
                }
                                    c++;
            }
        }
    }
    fprintf(g,"%d %d",c,P);
    fclose(f);
    fclose(g);
    return 0;
}
