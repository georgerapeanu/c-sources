#include <cstdio>
#include <unordered_map>
#include <fstream>
#define dif first
#define countt second
using namespace std;
FILE *f=fopen("facebook.in","r");
FILE *g=fopen("facebook.out","w");
unordered_map <long long,pair<long long,long long> > V;
long long i,N,K,val,st,dr,last,mid,ctr,minim=((1LL)<<30)+1;
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&val);
        V[val].countt++;
        V[val].dif=i-V[val].countt;
    }
    for(auto it:V)
    {
        if((it.second).countt>=K&&(it.second).dif<minim)
            minim=(it.second).dif;
    }
    fprintf(g,"%lld",minim);
    fclose(f);
    fclose(g);
    return 0;
}
