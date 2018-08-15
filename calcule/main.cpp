#include <cstdio>
using namespace std;
FILE *f=fopen("calcule.in","r");
FILE *g=fopen("calcule.out","w");
long long N,K,V,i,nr,u,S,j,best,FF[100005];
long long v[100005];
int main()
{
    v[0]=-1;
    fscanf(f,"%lld %lld",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V);
        S+=V;
        S%=K;
        FF[S]++;
        best=0;
        for(j=1;j<=u;j++)
        {
            if(v[j]<V&&v[best]<v[j])
                best=j;
        }
        if(best)
            v[best]=V;
        else
        {
            v[++u]=V;
        }
    }
    fprintf(g,"%lld\n",u);
    nr=FF[0]*(FF[0]+1)/2;
    for(i=1;i<K;i++)
    {
        nr=(nr+((FF[i]%20011)*((FF[i]-1)%20011)/2)%20011)%20011;
    }
    fprintf(g,"%lld",nr);
    fclose(f);
    fclose(g);
    return 0;
}
