#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("gard5.in","r");
FILE *g=fopen("gard5.out","w");
int N;
long long moduri=1,cost=0;
int V[105],maxim,tmin,tmax;
int mini[105];
int maxi[105];
int special[105];
int main()
{
    int len=0;
    special[++len]=0;
    fscanf(f,"%d",&N);
    tmin=N+1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        if(maxim<V[i])
        {
            maxim=V[i];
            special[++len]=i;
            maxi[len]=tmax;
            mini[len]=tmin;
            tmax=0;tmin=N+1;
            continue;
        }
        tmax=max(tmax,V[i]);
        tmin=min(tmin,V[i]);
    }
    V[N+1]=N+1;
    special[++len]=N+1;
    maxi[len]=tmax;
    mini[len]=tmin;
    for(int i=1;i<=len;i++)
    {
        if(special[i]==special[i-1]+1) continue;
        cost+=2*(maxi[i]-mini[i])+abs(V[special[i-1]]-mini[i])+abs(V[special[i]]-maxi[i]);
        moduri*=(1+(maxi[i]!=mini[i]));
    }
    fprintf(g,"%lld %lld",cost,moduri);
    fclose(f);
    fclose(g);
    return 0;
}
