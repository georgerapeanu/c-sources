#include <cstdio>
#define MOD 9901
using namespace std;
int N,V[1005],best[1005],i,j,nr[1005],maxim,nrmax;
FILE *f=fopen("subsiruri.in","r");
FILE *g=fopen("subsiruri.out","w");
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        best[i]=1;
        nr[i]=1;
        for(j=i-1;j>0;j--)
        {
            if(V[j]<V[i])
            {
                if(best[i]<best[j]+1)
                {
                    best[i]=best[j]+1;
                    nr[i]=nr[j];
                }
                else if(best[i]==best[j]+1)
                    {nr[i]+=nr[j];nr[i]%=MOD;}
            }
        }
        if(best[i]>maxim)
        {
            maxim=best[i];
            nrmax=nr[i]%MOD;
        }
        else if(best[i]==maxim)
            {nrmax+=nr[i];nrmax%=MOD;}
    }
    fprintf(g,"%d\n%d",maxim,nrmax);
    fclose(f);
    fclose(g);
}
