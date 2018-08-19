#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f=fopen("joc14.in","r");
FILE *g=fopen("joc14.out","w");
pair <int,int> V[10];
int N,nr,i,lat,j,cifdif,afis;
int main()
{
    fscanf(f,"%d",&N);
    for(i=0;i<=9;i++)
    {
        V[i].first=0;
        V[i].second=i;
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&nr);
        if(V[nr].first==0)
            cifdif++;
        V[nr].first++;
    }
    sort(V,V+10);
    lat=int(sqrt(double(N)));
    fprintf(g,"%d\n%d\n",cifdif,lat);
    i=1;
    N=lat*lat;
    j=9;
    afis=V[9].first;
    while(i<=N)
    {
        fprintf(g,"%d",V[j].second);
        if(i%lat==0)
            fprintf(g,"\n");
        i++;
        if(i>afis)
        {
            j--;
            afis+=V[j].first;
        }
    }
    return 0;
}
