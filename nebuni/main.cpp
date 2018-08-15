#include <cstdio>
using namespace std;
FILE *f=fopen("nebuni.in","r");
FILE *g=fopen("nebuni.out","w");
bool dp[2000002],ds[2000002];
int S[2000002];
int M,i,x,y,stx,sty,drx,dry,sst,sdr;
long long N,nrp,nrs,nr;
int main()
{
    fscanf(f,"%lld %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%ld %ld",&x,&y);
        dp[N-x+y]=1;
        ds[x+y-1]=1;
    }
    for(i=1;i<=2*N-1;i++)
    {
        if(dp[i]==1)
            if(i<=N)
                nrp+=i;
            else
                nrp+=(2*N-i);
        if(ds[i]==1)
            if(i<=N)
                nrs+=i;
            else
                nrs+=(2*N-i);
        if(i>1)
            S[i]=ds[i]+S[i-2];
        else
            S[i]=ds[i];
    }
    for(i=1;i<=2*N-1;i++)
    {
        if(dp[i])
        {
            if(i<=N)
            {
                drx=N;
                dry=i;
                sty=1;
                stx=N+1-i;
            }
            else
            {
                stx=1;
                sty=i-N+1;
                dry=N;
                drx=2*N-i;
            }
            sst=stx+sty-1;
            sdr=drx+dry-1;
            nr+=S[sdr]-S[sst-2];
        }
    }
    fprintf(g,"%lld",(N*N)-nrs-nrp+nr);
    fclose(f);
    fclose(g);
    return 0;
}
