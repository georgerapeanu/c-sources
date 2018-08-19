#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("jucarii.in","r");
FILE *g=fopen("jucarii.out","w");
int pas,V[20],N,K,P,i;
bool used[20];
bool ok()
{
    int best[20];
    for(int i=1;i<=N;i++)
    {
        best[i]=1;
        for(int j=1;j<i;j++)
        {
            if(V[j]<V[i])
            {
                best[i]=max(best[j]+1,best[i]);
            }
        }
        if(best[i]>=K)
            return 1;
    }
    return 0;
}
int back(int s,int p,int n)
{
    if(s>n)
        {if(ok())pas++;}
    else
    {
        if(pas<p)
        {
            for(int i=1;i<=n&&pas<p;i++)
            {
                if(!used[i]&&pas<p)
                {
                    used[i]=1;
                    V[s]=i;
                    back(s+1,p,n);
                    used[i]=0;
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d %d %d",&N,&K,&P);
    back(1,P,N);
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
