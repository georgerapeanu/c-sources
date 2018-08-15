#include <cstdio>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <bitset>
#define MAX 1000000
#define XMAX 1000000000000000000LL
using namespace std;
FILE *f=fopen("ubercool.in","r");
FILE *g=fopen("ubercool.out","w");
bitset<1000001> B;
unordered_set <long long> S;
long long T,N;
int main()
{
    B[0]=B[1]=1;
    for(int i=2;i*i<=MAX;i++)
    {
        if(!B[i])
        {
            for(int j=i*i;j<=MAX;j+=i)
            {
                B[j]=1;
            }
        }
    }
    for(long long i=2;i<=MAX;i++)
    {
        if(!B[i])
       {
            for(long long j=i*i,pre=i;j<=XMAX&&j/i==pre;pre=j,j*=i)
                S.insert(j);
           // printf("%d\n",S.find(864691128455135232)!=S.end());
       }
    }

    fscanf(f,"%lld",&T);
    while(T)
    {
        fscanf(f,"%lld",&N);
        if(S.find(N)!=S.end())
        {
            fprintf(g,"DA\n");
        }
        else
        {
            long long nr=sqrt(N);
            if(nr<=1)
            {fprintf(g,"NU\n");}
            else if(nr*nr==N)
            {
                bool ok=0;
                for(long long i=2;i*i<=nr;i++)
                {
                    if(nr%i==0)
                    {
                        fprintf(g,"NU\n");
                        ok=1;break;
                    }
                }
                if(!ok)
                    fprintf(g,"DA\n");
            }
            else
                fprintf(g,"NU\n");
        }
        T--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
