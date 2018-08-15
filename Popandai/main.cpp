#include <cstdio>
#include <cstring>
#include <algorithm>
#define x first
#define y second
using namespace std;
FILE *f=fopen("popandai.in","r");
FILE *g=fopen("popandai.out","w");
int N,K;
pair<int,int> V[305];
int sub[305][305];
long long up[305];
long long down[305];
long long rez=1LL<<52;
long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
    return 1LL*a.x*b.y+1LL*b.x*c.y+1LL*c.x*a.y-1LL*a.x*c.y-1LL*b.x*a.y-1LL*c.x*b.y;
}
int cate(int i,int j,int k)
{
    if(V[j]<V[i]&&V[j]<V[k])swap(i,j);
    else if(V[k]<V[i]&&V[k]<=V[j])swap(i,k);
    if(V[k]<V[j])swap(j,k);
    if(det(V[i],V[k],V[j])<0)
    {
        return sub[i][k]-sub[i][j]-sub[j][k]-1;
    }
    else
    {
        return sub[i][j]+sub[j][k]-sub[i][k];
    }
}
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)fscanf(f,"%d %d",&V[i].x,&V[i].y);
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            for(int k=i+1;k<j;k++)
            {
                sub[i][j]+=(det(V[i],V[j],V[k])<0);
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            for(int k=0;k<=N+1;k++)up[k]=down[k]=1LL<<52;
            for(int k=1;k<=N;k++)
            {
                if(k==i||k==j)continue;
                long long tmp=det(V[i],V[j],V[k]);
                if(tmp<0)
                {
                    int t=cate(i,j,k);
                    down[t]=min(down[t],-tmp);
                }
                else
                {
                    int t=cate(i,j,k);
                    up[t]=min(up[t],tmp);
                }
            }
            for(int k=N;k;k--){up[k]=min(up[k+1],up[k]);down[k]=min(down[k+1],down[k]);}
            for(int k=0;k<=K;k++)rez=min(rez,up[k]+down[K-k]);
        }
    }
    fprintf(g,"%lld.%lld",rez/2,5*(rez%2));
    fclose(f);
    fclose(g);
    return 0;
}
