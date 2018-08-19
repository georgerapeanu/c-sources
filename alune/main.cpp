#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("alune.in","r");
FILE *g=fopen("alune.out","w");
int N,M,i,j,minim=2000000005;
long long A;
long long LCM=1;
int B;
bool stillok=1;
long long GCD(long long a,long long b)
{
    if(b==0)
        return a;
    return GCD(b,a%b);
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        {
            fscanf(f,"%lld",&A);
            if(stillok)
            {
                LCM=(A*LCM)/GCD(A,LCM);
                if(LCM>2000000005)
                {
                    stillok=0;
                    LCM=2000000005;
                }
            }
            if(A<minim)
                minim=A;
        }
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&B);
        if(B%LCM<minim)
            fputc('1',g);
        else
            fputc('0',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
