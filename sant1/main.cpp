#include <cstdio>
#include <vector>
#include <algorithm>
#define st first
#define dr second
#define inf 1000000000
using namespace std;
FILE *f=fopen("sant1.in","r");
FILE *g=fopen("sant1.out","w");
int N,i,p,st,dr,val;
typedef pair<int,int> interval;
interval V[10005];
interval a;

int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
    }
    sort(V+1,V+1+N);
    i=1;
    while(i<=N)
    {
        a=make_pair(-inf,inf);
        st=i;
        while(a.st<=a.dr&&i<=N)
        {
            if(max(a.st,V[i].dr)>min(a.dr,V[i].dr))
            {
                val=a.st;
            }
            a=make_pair(max(a.st,V[i].st),min(a.dr,V[i].dr));
            if(a.st<=a.dr&&i<=N)
            i++;
            dr++;
        }
        p++;
    }
    fprintf(g,"%d",p);
    return 0;
}
