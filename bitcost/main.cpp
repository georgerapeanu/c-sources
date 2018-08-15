#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("bitcost.in","r");
FILE *g=fopen("bitcost.out","w");
long long C[65],V[65];
long long N,K,a,b,i,costa,costb,j,maxim;
int main()
{
    fscanf(f,"%lld%lld",&K,&N);
    for(i=0;i<K;i++)
        fscanf(f,"%lld",&C[i]);
    V[0]=max(0LL,C[0]);
    for(i=1;i<K;i++)
    {
        V[i]=max(0LL,C[i])+V[i-1];
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld%lld",&a,&b);
        j=K-1;
        costa=costb=0;
        while(j>=0&&((a&((1LL)<<j))>0)==((b&((1LL)<<j))>0))
        {
            costa+=((a&((1LL)<<j))>0)*C[j];
            costb+=((b&((1LL)<<j))>0)*C[j];
            j--;
        }
        costa+=((a&((1LL)<<j))>0)*C[j];
        costb+=((b&((1LL)<<j))>0)*C[j];
        j--;
        maxim=-60000005;
        for(;j>=0;j--)
        {
            ///cazul a
            if(a&((1LL)<<j))
            {
                ;
            }
            else
            {
                if(j>0&&(costa+C[j]+V[j-1]>maxim))
                    maxim=costa+C[j]+V[j-1];
                else if(costa+C[j]>maxim&&!j)
                    maxim=costa+C[j];
            }
            costa+=((a&((1LL)<<j))>0)*C[j];
            ///cazul b
            if(b&((1LL)<<j))
            {
                if(j>0&&(costb+V[j-1]>maxim))
                    maxim=costb+V[j-1];
                else if(!j&&costb>maxim)
                    maxim=costb;
            }
            costb+=((b&((1LL)<<j))>0)*C[j];
        }
        maxim=max(costa,maxim);
        maxim=max(costb,maxim);
        fprintf(g,"%lld\n",maxim);
    }
    fclose(f);
    fclose(g);
    return 0;
}
