#include <algorithm>
#include <cstdio>
using namespace std;
FILE *f=fopen("mexc.in","r");
FILE *g=fopen("mexc.out","w");
struct data
{
    int x,y,val;
    bool operator < (const data &other)const
    {
        return val>other.val;
    }
}V[800*800+5];
int v[805][805];
int ind,N,M,D;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int T[802*802+5];
int SZ[802*802+5];
int R[805][805];
int hsh(int x,int y)
{
    return 801*x+y;
}
int fi(int a)
{
    if(!T[a])return a;
    return T[a]=fi(T[a]);
}
void u(int a,int b)
{
    a=fi(a);
    b=fi(b);
    if(a==b)return ;
    T[a]=b;
    SZ[b]+=SZ[a];
}
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&D);
    int ind=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            int val;
            fscanf(f,"%d",&val);
            v[i][j]=val;
            V[++ind]={i,j,val};
        }
    }
    sort(V+1,V+1+ind);
    int l=1,r=0,fl=0;
    while(l<=ind)
    {
        SZ[fi(hsh(V[l].x,V[l].y))]++;
        while(V[l].val==V[l+1].val&&l<ind)
        {
            l++;
            SZ[fi(hsh(V[l].x,V[l].y))]++;
        }
        while(V[l].val-V[r+1].val<=D&&r<ind)
        {
            r++;
            int x=V[r].x,y=V[r].y;
            for(int k=0;k<4;k++)
            {
                int xx=x+dx[k],yy=y+dy[k];
                if(xx&&yy&&xx<=N&&yy<=M&&V[l].val-v[xx][yy]<=D)
                {
                    u(hsh(x,y),hsh(xx,yy));
                }
            }
        }
        for(int i=fl+1;i<=l;i++)
        {
            R[V[i].x][V[i].y]=SZ[fi(hsh(V[i].x,V[i].y))];
        }
        fl=l;
        l++;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            fprintf(g,"%d ",R[i][j]);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
