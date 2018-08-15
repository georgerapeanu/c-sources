#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("cutii.in","r");
FILE *g=fopen("cutii.out","w");
int N,T;
struct ceva{int x,y,z;}V[3501];
int AIB[3501][3501];
int dp[3501];
bool cmp(ceva a,ceva b)
{
    if(a.x!=b.x)return a.x<b.x;
    if(a.y!=b.y)return a.y<b.y;
    return a.z<b.z;
}
void u(int x,int y,int val,bool c)
{
    for(int i=x;i<=N;i+=(-i)&i)for(int j=y;j<=N;j+=(-j)&j)AIB[i][j]=max(AIB[i][j]*(!c),val);
}
int q(int x,int y)
{
    int rez=0;
    for(int i=x;i;i-=(-i)&i)for(int j=y;j;j-=(-j)&j)rez=max(rez,AIB[i][j]);
    return rez;
}
int main()
{
    fscanf(f,"%d %d",&N,&T);
    while(T--)
    {
        for(int i=1;i<=N;i++)fscanf(f,"%d %d %d",&V[i].x,&V[i].y,&V[i].z);
        sort(V+1,V+1+N,cmp);
        int last=1,rez=0;
        for(int i=1;i<=N;i++)
        {
            if(V[last].x!=V[i].x)
            {
                while(last<i){u(V[last].y,V[last].z,dp[last],0);last++;}
            }
            dp[i]=q(V[i].y-1,V[i].z-1)+1;
            rez=max(rez,dp[i]);
        }
        fprintf(g,"%d\n",rez);
        for(int i=1;i<=N;i++)u(V[i].y,V[i].z,0,1);
    }
    fclose(f);
    fclose(g);
    return 0;
}
