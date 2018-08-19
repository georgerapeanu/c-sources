#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("tren.in","r");
FILE *g=fopen("tren.out","w");
int N;
long long V[1024];
int i,K;
long long rez;
long long suma(int st,long long *v)
{
    long long s=0;
    for(i=0;i<1<<(N-st);i++)
        s+=v[i];
    return s;
}
long long desp(int st,long long *v)
{
    if(st<K)
    {
        long long v1[1<<(N-st)],v2[1<<(N-st)];
        for(i=0;i<1<<(N-st+1);i++)
        {
            if(i%2==0)
                v1[i/2]=v[i];
            else
                v2[i/2]=v[i];
        }
        return max(desp(st+1,v1),desp(st+1,v2));
    }
    else
        return suma(st-1,v);
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=0;i<1<<N;i++)
        fscanf(f,"%lld",&V[i]);
    rez=desp(1,V);
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
