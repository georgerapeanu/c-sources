#include <cstdio>
#include <iostream>
#include <algorithm>
#define ushrt unsigned short
using namespace std;
FILE *f=fopen("flota.in","r");
FILE *g=fopen("flota.out","w");
ushrt N;
int M;
int K;
int i,j;
ushrt nr,a,b;
ushrt parinte[50005],noduri[50005];
ushrt rez[100005];
pair <ushrt,int> lungimi[100005];
pair<ushrt,pair<ushrt,ushrt> > muchii[1000005];
ushrt fi(ushrt x)
{
    if(parinte[x]==0)
        return x;
    else
        parinte[x]=fi(parinte[x]);
    return parinte[x];
}
void un(ushrt x,ushrt y)
{
    if(noduri[x]>noduri[y])
    {
        noduri[x]+=noduri[y];
        parinte[y]=x;
    }
    else
    {
        noduri[y]+=noduri[x];
        parinte[x]=y;
    }
}
int main()
{
    fscanf(f,"%hu %d %d",&N,&M,&K);
    for(i=1;i<=M;i++)
        fscanf(f,"%hu %hu %hu",&muchii[i].second.first,&muchii[i].second.second,&muchii[i].first);
    sort(muchii+1,muchii+1+M);
    for(i=1;i<=K;i++)
       {
           fscanf(f,"%hu",&lungimi[i].first);
           lungimi[i].second=i;
        }
    sort(lungimi+1,lungimi+K+1);
    j=M;nr=N;
    for(i=K;i>0;i--)
    {
        while(j>0&&muchii[j].first>=lungimi[i].first)
        {
            a=fi(muchii[j].second.first);
            b=fi(muchii[j].second.second);
            if(a!=b)
            {
                nr--;
                un(a,b);
            }
            j--;
        }
        rez[lungimi[i].second]=nr;
    }
    for(i=1;i<=K;i++)
        fprintf(g,"%hu\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
