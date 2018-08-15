#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;
FILE *f=fopen("cuburi3.in","r");
FILE *g=fopen("cuburi3.out","w");
int i,j,N,maxim,K,cuburi[4005];
pair <int,pair<int,int> > V[4005];
long long best[4005];
int rez[4005];
int P[4005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].first,&V[i].second.first);
        V[i].second.second=i;
    }
    sort(V+1,V+1+N);
    for(i=N;i>0;i--)
    {
        best[i]=V[i].first;
        for(j=N;j>i;j--)
        {
            if(V[j].second.first>=V[i].second.first&&best[j]+V[i].first>best[i])
                {best[i]=best[j]+V[i].first;P[i]=j;}
        }
        if(best[i]>best[maxim])
            maxim=i;
    }
    i=maxim;
    while(i)
    {
        cuburi[++K]=V[i].second.second;
        i=P[i];
    }
    fprintf(g,"%d %d\n",K,best[maxim]);
    for(i=K;i>0;i--)
        fprintf(g,"%d\n",cuburi[i]);
    fclose(f);
    fclose(g);
    return 0;
}
