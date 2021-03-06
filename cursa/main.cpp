#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("cursa.in","r");
FILE *g=fopen("cursa.out","w");
double d[505];
int i,N,c[505],poz,poz2,j;
short cod[1000];
pair <double,int> top[505];
pair <double,int> depasiri[505];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %lf",&c[i],&d[i]);
        cod[c[i]]=i;
        top[i]=make_pair(0,c[i]);
    }
    i=1;
    for(i=1;i<=N;i++)
    {
        top[i].first=d[N]-(d[i]-d[i-1])/2;
    }
    sort(top+1,top+1+N);
    for(i=1;i<=N;i++)
        {fprintf(g,"%d ",top[i].second);top[i]=make_pair(0,c[i]);}
    fprintf(g,"\n");
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            if(cod[top[j].second]==i)
            {
                poz=j;
                top[j].first+=(d[i]-d[i-1])/2;
            }
            else
                top[j].first+=d[i]-d[i-1];
        }
        depasiri[0].second=0;
        while(poz>1&&top[poz].first<top[poz-1].first)
        {
            poz--;
            depasiri[++depasiri[0].second]=top[poz];
            swap(top[poz],top[poz+1]);
        }
        if(depasiri[0].second)
        {fprintf(g,"%d %d %d ",i,top[poz].second,depasiri[0].second);
        sort(depasiri+1,depasiri+1+depasiri[0].second);
        for(j=depasiri[0].second;j>0;j--)
            fprintf(g,"%d ",depasiri[j].second);
        fprintf(g,"\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
