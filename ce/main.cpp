#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("ce.in","r");
FILE *g=fopen("ce.out","w");
bool B[1010][1010];
int i,j,N,M,k,d,a,b;
typedef struct{int x,y;} punct;
queue <punct> Q;
char C[1005][1005];
const int dirx[]={0,-1,0,1,0,-1,1,1,-1};
const int diry[]={0,0,1,0,-1,1,1,-1,-1};
short T;
int main()
{
    fscanf(f,"%hd",&T);
    for(k=1;k<=T;k++)
    {
        ///initializare
        fscanf(f,"%d %d\n",&N,&M);
        for(i=1;i<=N;i++)
        {
            fgets(C[i]+1,1005,f);
            for(j=1;j<=M;j++)
                B[i+1][j+1]=C[i][j]=='X' ? 1:0;
        }///interioare(separare)
        //bordare
        for(i=0;i<=N+3;i++)
            B[i][0]=B[i][N+3]=1;
        for(i=0;i<=M+3;i++)
            B[0][i]=B[N+3][i]=1;
        //separare
        Q.push({1,1});
        while(!Q.empty())
        {
            int x,y;
            x=(Q.front()).x;
            y=(Q.front()).y;
            B[x][y]=1;
            Q.pop();
            for(i=1;i<=8;i++)
                if(B[x+dirx[i]][y+diry[i]]==0)
                    Q.push({x+dirx[i],y+diry[i]});
        }
        ///corpuri conexexe
        for(i=2;i<=N+1;i++)
        {
            for(j=2;j<=M+1;j++)
            {
                if(C[i][j]=='X')
                {
                    Q.push({i,j});
                    while(!Q.empty())
                    {
                        int x,y;
                        x=(Q.front()).x;
                        y=(Q.front()).y;
                        C[x][y]='O';
                        Q.pop();
                        for(d=1;d<=8;d++)
                            if(C[x+dirx[d]][y+diry[d]]=='X')
                                Q.push({x+dirx[d],y+diry[d]});
                    }
                    a++;
                }
                if(B[i][j]==0)
                {
                    Q.push({i,j});
                     while(!Q.empty())
                    {
                        int x,y;
                        x=(Q.front()).x;
                        y=(Q.front()).y;
                        B[x][y]=1;
                        Q.pop();
                        for(d=1;d<=4;d++)
                            if(B[x+dirx[d]][y+diry[d]]==0)
                                Q.push({x+dirx[d],y+diry[d]});
                    }
                    b++;
                }

            }
        }
        fprintf(g,"%d\n",a-b);
        a=b=0;
    }
    fclose(f);
    fclose(g);
    return 0;
}
