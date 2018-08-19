#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("fibo.in","r");
FILE *g=fopen("fibo.out","w");
int nr,N;
int fib[31];
bitset<1000005> B;
bitset<31> F;
void btr(int st,int dr,int val,bool voie)
{
    if(val>N) return;
    if(st>dr)
    {
        if(F[dr]==1&&F[st]==1&&st==dr+1) return;
        if(B[val]) return;
        nr++;
        B[val]=1;
        return ;
    }
    if(voie)
    {
        F[st]=F[dr]=1;
        btr(st+1,dr-1,val+fib[st]+fib[dr]-(st==dr)*fib[st],0);
        F[st]=F[dr]=0;
    }
    if(st!=2)
    {
        btr(st+1,dr-1,val,1);
    }
}
int main()
{
    fscanf(f,"%d",&N);
    fib[1]=1;
    for(int i=2;i<=30;i++)
    {
        fib[i]=fib[i-1]+fib[i-2];
        btr(2,i,0,1);
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
