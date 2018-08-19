#include <cstdio>
#include <map>
using namespace std;
FILE *f=fopen("schi1.in","r");
FILE *g=fopen("schi1.out","w");
map <int,int> M;
int N,K,nr,i,maxim,val;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        if(val<=maxim)
            nr++;
        else
        {
            M[maxim]=nr;
            nr=1;
            maxim=val;
        }
    }
    M[maxim]=nr;
    fscanf(f,"%d",&K);
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d",&val);
        fprintf(g,"%d ",M[val]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
