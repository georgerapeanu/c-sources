#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("rating.in","r");
FILE *g=fopen("rating.out","w");
typedef pair<int,pair<int,int> > data;
int N,M,i,j,val,nr;
vector <data> V;
bool mycmp(data a,data b)
{
    if(a.first!=b.first)
        return a.first<b.first;
    if(a.second.first!=b.second.first)
        return a.second.first>b.second.first;
    return a.second.second<b.second.second;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    V.push_back(data(0,make_pair(0,0)));
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&val);
            V.push_back(data(j,make_pair(val,i)));
        }
    }
    sort(V.begin(),V.end(),mycmp);
    nr=1;
    for(i=1;i<=M;i++)
    {
        for(j=1;j<=N;j++)
        {
            fprintf(g,"%d ",V[nr].second.second);
            nr++;
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
