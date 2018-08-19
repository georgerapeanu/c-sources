#include <cstdio>
#include <algorithm>
#include <fstream>
#define cost first
#define ind second.first
#define nr second.second
using namespace std;
FILE *f=fopen("costuri.in","r");
FILE *g=fopen("costuri.out","w");
int N,Q,P,C;
pair<int,pair<int,int> > V[100005];
int prod(int val)
{
    if(!val)
        return 0;
    int prod=1;
    while(val)
    {
        prod*=(val%10);
        val/=10;
    }
    return prod;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i].nr);
        V[i].ind=i;
        V[i].cost=prod(V[i].nr);
    }
    sort(V+1,V+1+N);
    fscanf(f,"%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        fscanf(f,"%d%d",&P,&C);
        int st=1,dr=N;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(V[mid].cost>=C)
                dr=mid;
            else
                st=mid+1;
        }
        if(st+P-1>N)
        {
            fprintf(g,"-1\n");continue;
        }
        if(V[st+P-1].cost==C)
            fprintf(g,"%d\n",V[st+P-1].nr);
        else
            fprintf(g,"-1\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
