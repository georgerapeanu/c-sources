#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("hercule.in","r");
FILE *g=fopen("hercule.out","w");
int N,nrcf;
long long K,i;
long long V[32],ad=1;
double l,l2;
int main()
{
    fscanf(f,"%d",&N);
    l2=log10(2);
    while(N--)
    {
        ad=1;
        fscanf(f,"%lld",&K);
        l=log10(K)/l2;
        if(l!=(long long)l)
          nrcf=l+1;
        else
            nrcf=l;
        K-=(nrcf+1)*nrcf/2;
        K--;i=3;
        while(K>=0&&i<=nrcf)
        {
            if(K>=(nrcf-i+1)*ad)
            {
                K-=(nrcf-i+1)*ad;
                V[i]=ad;
                V[nrcf+1]-=ad;
            }
            else
            {
                V[i]+=K/(nrcf-i+1);
                V[nrcf+1]-=K/(nrcf-i+1);
                K%=(nrcf-i+1);
                V[nrcf+1]--;
                V[nrcf-K+1]++;
                K=0;
            }
            ad=ad*2+1;
            i++;
        }
        if(K!=0)
            fprintf(g,"-1\n");
        else
        {
            ad=0;
            fprintf(g,"%d\n",nrcf);
            for(i=1;i<=nrcf;i++)
            {
                ad+=V[i];
                fprintf(g,"%lld ",i+ad);
                V[i]=0;
            }
            fprintf(g,"\n");
            V[nrcf+1]=0;
        }
    }
    return 0;
}
