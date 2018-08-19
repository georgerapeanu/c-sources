#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("bile.in","r");
FILE *g=fopen("bile.out","w");
int N;
pair<int,int> V[250*250+5];
bool M[255][255];
int T[250*250+5];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int rez[250*250+5];
int fi(int nod)
{
    if(T[nod]<0)return nod;
    return T[nod]=fi(T[nod]);
}
void u(int x,int y)
{
    x=fi(x);
    y=fi(y);
    if(x==y)return ;
    T[y]+=T[x];
    T[x]=y;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N*N;i++)
    {
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
        T[i]=-1;
    }
    for(int i=N*N;i;i--)
    {
        int x=V[i].first,y=V[i].second;
        M[x][y]=1;
        for(int k=0;k<4;k++)
        {
            int nx=x+dx[k];
            int ny=y+dy[k];
            if(nx&&ny&&nx<=N&&ny<=N&&M[nx][ny])u((x-1)*N+y,(nx-1)*N+ny);
        }
        rez[i]=max(rez[i+1],-T[fi((x-1)*N+y)]);
    }
    for(int i=2;i<=N*N+1;i++)fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
