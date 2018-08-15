#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("scenariu.in","r");
FILE *g=fopen("scenariu.out","w");
long long val1,val2,val3;
int x,y,N,K,S,a;
void inv(int a,int b)
{
    if(b==0)
    {
        x=1;
        y=0;
    }
    else
    {
        inv(b,a%b);
        int x0,y0;
        x0=y;
        y0=x-y*(a/b);
        x=x0;y=y0;
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=K;i++)
    {fscanf(f,"%d",&a);S+=a;}
    long long val=1;
    val=val2=val3=1;
    N--;S--;
    for(int i=1;i<=N;i++)
    {
        val=(val*i)%MOD;
        if(i==N) val1=val;
        if(i==S) val2=val;
        if(i==N-S) val3=val;
    }
    inv(val2,MOD);val2=(x%MOD+MOD)%MOD;
    inv(val3,MOD);val3=(x%MOD+MOD)%MOD;
    fprintf(g,"%d",(((val1*val2)%MOD)*val3)%MOD);
    fclose(f);
    fclose(g);
    return 0;
}
