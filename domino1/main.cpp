#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;
FILE *f=fopen("domino1.in","r");
FILE *g=fopen("domino1.out","w");
pair <int,int> V[1005];
int i,N,u,a,b,maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
    }
    sort(V+1,V+1+N);
    u=V[1].first;
    for(i=1;i<=N;i++)
    {
        if(u>=V[i].first)
        {
            u=max(u,V[i].first+V[i].second);
            b++;
        }
        else
        {
            u=V[i].first+V[i].second;
            a++;
            if(b>maxim)
                maxim=b;
            b=1;
        }
    }
    a++;
    if(b>maxim)
        maxim=b;
    fprintf(g,"%d %d",a,maxim);
    return 0;
}
