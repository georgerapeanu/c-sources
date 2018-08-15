#include <cstdio>
using namespace std;
FILE *f,*g;
long long n,m,i,j,a,b,nrc,k,ma[10001][10001],nrb;
bool viz[10001],c,v[10001],ve[10001];
void dfs(long long nr)
{
    int j;
    viz[nr]=1;
    for(j=1;j<=n;j++)
    {
        if(ma[nr][j]==1&&viz[j]==0)
        {
            dfs(j);
        }
    }
}
void df(long long nr,long long prev)
{
    if(c==0)
    {
        int j;
        for(j=1;j<=n&&c==0;j++)
        {
            if(ve[j]==0&&i!=j&&ma[nr][j]==1&&j!=prev)
            {
                ve[j]=1;
                df(j,nr);
                ve[j]=0;
            }
            else if(i==j&&ma[nr][j]==1&&j!=prev)
            {
                c=1;
            }
        }
        if(c==1)
        {
            v[nr]=1;
        }
    }
}
int main()
{
    f=fopen("sosele.in","r");
    g=fopen("sosele.out","w");
    fscanf(f,"%lld %lld",&n,&m);
    for(i=1;i<=m;i++)
    {
        fscanf(f,"%lld %lld",&a,&b);
        ma[a][b]=ma[b][a]=1;
    }
    for(i=1;i<=n;i++)
    {
        if(viz[i]==0)
        {
            dfs(i);
            nrc++;
        }
    }
    nrc--;
    for(i=1;i<=n;i++)
    {
        if(!v[i])
        {
            df(i,0);
        }
        c=0;
    }
    for(i=1;i<=n;i++)
    {
        if(v[i]==0)
        {
            for(j=1;j<=n;j++)
            {
                if(ma[i][j]==1)
                {
                    v[i]=v[j]=1;
                    nrb++;
                    break;
                }
            }
        }
    }
    fprintf(g,"%lld\n%lld",nrc,nrb);
    return 0;
}
