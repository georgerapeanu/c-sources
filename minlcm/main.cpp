#include <cstdio>
#include <bitset>
#define VMAX 100000
using namespace std;
FILE *f=fopen("minlcm.in","r");
FILE *g=fopen("minlcm.out","w");
bitset <VMAX+5> V;
long long rez,val;
int N;
int T;
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        rez=9999900000;
        fscanf(f,"%d",&N);
        V.reset();
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%d",&val);V[val]=1;
        }
        for(int i=1;i<=VMAX;i++)
        {
            long long p=1,nr=0;
            for(int j=i;j<=VMAX;j+=i)
            {
                if(V[j])
                {
                    nr++;
                    p=p*j;
                    if(nr==2) {rez=min(rez,p/i);break;}
                }
            }
        }
        fprintf(g,"%lld\n",rez);
        T--;
    }
    return 0;
}
