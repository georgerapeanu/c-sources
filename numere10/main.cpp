#include <cstdio>
#define Nmax 10000
#define Vmax 1000000
using namespace std;
FILE *f=fopen("numere10.in","r");
FILE *g=fopen("numere10.out","w");
bool E[Vmax+5];
long long val,nr;
long long N;
long long i,j;
int main()
{
    E[1]=E[0]=1;
    for(i=2;i*i<=Vmax;i++)
    {
        if(!E[i])
        {
            for(j=i*i;j<=Vmax;j+=i)
                E[j]=1;
        }
    }
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&val);
        for(j=2;j*j<val;j++)
        {
            if(val%j==0&&(!E[j])&&(!E[val/j]))
            {nr++;break;}
        }
    }
    fprintf(g,"%lld",nr);
    fclose(f);
    fclose(g);
    return 0;
}
