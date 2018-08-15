#include <cstdio>
#include <fstream>
#include <queue>
using namespace std;
FILE *f=fopen("roboti1.in","r");
FILE *g=fopen("roboti1.out","w");
struct{bool E;int x,y,relx,rely;} V[55];
int M[2][55][55];
int i;
int p,q;
int n,m,nr,maxim,j,x,y;
char C[55][55];
char c;
int F[55][55];
typedef pair<int,int> data;
queue <data> Q;
int main()
{
    fscanf(f,"%d %d\n%d",&p,&q,&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d %d %c",&V[i].x,&V[i].y,&c);
        if(c=='N')
            V[i]={1,V[i].x,V[i].y,-1,0};
        else if(c=='E')
            V[i]={1,V[i].x,V[i].y,0,1};
        else if(c=='S')
            V[i]={1,V[i].x,V[i].y,1,0};
        else
            V[i]={1,V[i].x,V[i].y,0,-1};
        F[V[i].x][V[i].y]=1;
    }
    nr=n;
    fscanf(f,"%d\n",&m);
    for(i=1;i<=n;i++)
        fgets(C[i]+1,55,f);
    for(j=1;j<=m;j++)
    {
        for(i=1;i<=n;i++)
        {
            if(V[i].E)
            {
                if(C[i][j]=='F')
                {
                    V[i].x+=V[i].relx;
                    V[i].y+=V[i].rely;
                    if(M[j%2][V[i].x][V[i].y]==0)
                    {
                        M[j%2][V[i].x][V[i].y]=i;
                    }
                    else
                    {
                        V[i].E=0;
                        V[M[j%2][V[i].x][V[i].y]].E=0;
                        Q.push(make_pair(V[i].x,V[i].y));
                    }
                    M[(j+1)%2][V[i].x-V[i].relx][V[i].y-V[i].rely]=0;
                    F[V[i].x][V[i].y]++;
                    if((1>V[i].x||p<V[i].x)||(1>V[i].y||q<V[i].y)){M[j%2][V[i].x][V[i].y]=0;V[i].E=0;};
                }
                else if(C[i][j]=='L')
                {
                    if(V[i].relx==-1&&V[i].rely==0)
                        V[i]={V[i].E,V[i].x,V[i].y,0,-1};
                    else if(V[i].relx==0&&V[i].rely==-1)
                        V[i]={V[i].E,V[i].x,V[i].y,1,0};
                    else if(V[i].relx==1&&V[i].rely==0)
                        V[i]={V[i].E,V[i].x,V[i].y,0,1};
                    else if(V[i].relx==0&&V[i].rely==1)
                        V[i]={V[i].E,V[i].x,V[i].y,-1,0};
                    if(M[j%2][V[i].x][V[i].y]!=0)
                    {
                        V[i].E=0;
                        V[M[j%2][V[i].x][V[i].y]].E=0;
                        Q.push(make_pair(V[i].x,V[i].y));
                    }
                    else
                        M[j%2][V[i].x][V[i].y]=i;
                    M[(j+1)%2][V[i].x][V[i].y]=0;
                }
                else
                {
                    if(V[i].relx==-1&&V[i].rely==0)
                        V[i]={V[i].E,V[i].x,V[i].y,0,1};
                    else if(V[i].relx==0&&V[i].rely==-1)
                        V[i]={V[i].E,V[i].x,V[i].y,-1,0};
                    else if(V[i].relx==1&&V[i].rely==0)
                        V[i]={V[i].E,V[i].x,V[i].y,0,-1};
                    else if(V[i].relx==0&&V[i].rely==1)
                        V[i]={V[i].E,V[i].x,V[i].y,1,0};
                    if(M[j%2][V[i].x][V[i].y]!=0)
                    {
                        V[i].E=0;
                        V[M[j%2][V[i].x][V[i].y]].E=0;
                        Q.push(make_pair(V[i].x,V[i].y));
                    }
                    else
                        M[j%2][V[i].x][V[i].y]=i;
                    M[(j+1)%2][V[i].x][V[i].y]=0;
                }
            }
        }
           while(!Q.empty())
                {M[j%2][(Q.front()).first][(Q.front()).second]=0;Q.pop();}
    }
    nr=0;
    for(i=1;i<=n;i++)
        nr+=V[i].E;
    fprintf(g,"%d\n",nr);
    for(i=1;i<=p;i++)
    {
        for(j=1;j<=q;j++)
        {
            if(F[i][j]>maxim)
            {
                maxim=F[i][j];
                x=i;
                y=j;
            }
        }
    }
    fprintf(g,"%d %d %d",x,y,maxim);
    fclose(f);
    fclose(g);
    return 0;
}
