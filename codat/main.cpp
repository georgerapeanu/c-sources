#include <cstdio>
using namespace std;
FILE *f=fopen("codat.in","r");
FILE *g=fopen("codat.out","w");
long long X[1000005];
int N,i;
int S[1000005],rez[1000005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&X[i]);
        while(S[0]&&X[i]>=X[S[S[0]]])
            {S[0]--;}
        if(S[0]==0)
            rez[i]=-1;
        else
            rez[i]=S[S[0]];
        S[++S[0]]=i;
    }
    S[0]=0;
    for(i=N;i>0;i--)
    {
        while(S[0]&&X[i]>=X[S[S[0]]])
            {S[0]--;}
        if(S[0])
        {
            if(rez[i]==-1)
                rez[i]=S[S[0]];
            else if(i-rez[i]>=S[S[0]]-i)
                rez[i]=S[S[0]];
        }
        S[++S[0]]=i;
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
