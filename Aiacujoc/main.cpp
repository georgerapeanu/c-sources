#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("aiacujoc.in","r");
FILE *g=fopen("aiacujoc.out","w");
int N,M,K,T;
long long st[2000005];
long long dr[2000005];
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        memset(st,0,sizeof(st));
        memset(dr,0,sizeof(dr));
        fscanf(f,"%d %d %d",&N,&M,&K);
        for(int i=0;i<=K&&i<N;i++)
        {
            int j=(N-i-1)%(K+1);
            st[i^j]+=(((N-1)/(K+1))+((N-1)%(K+1)>=i));
        }
        for(int i=0;i<=K&&i<M;i++)
        {
            int j=(M-i-1)%(K+1);
            dr[i^j]+=(((M-1)/(K+1))+((M-1)%(K+1)>=i));
        }
        long long rez=0;
        for(int i=0;i<=2*K;i++)
            rez+=st[i]*dr[i];
        fprintf(g,"%lld\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
