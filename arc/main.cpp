#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("arc.in","r");
FILE *g=fopen("arc.out","w");
pair <int,int> vecini[10005];
pair <int,int> data[10005];
pair <int,int> lungimi[10005];
int i,j,N,c,V,fV,ctr,k,rez,sj,sk;
bool used[100005];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.first!=b.first)
        return a.first<b.first;
    return a.second>b.second;
}
int main()
{
    fscanf(f,"%d%d",&c,&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V);
        if(V==fV)
            data[ctr].second++;
        else
            {
                lungimi[ctr]=make_pair(data[ctr].second,ctr);
                vecini[ctr]=make_pair(ctr-1,ctr+1);
                ctr++;
                data[ctr]=make_pair(V,1);
            }
        fV=V;
    }
    lungimi[ctr]=make_pair(data[ctr].second,ctr);
    if(c==1)
        fprintf(g,"%d",ctr);
    else
    {
        rez=N;
        sort(lungimi+1,lungimi+ctr+1,cmp);
        for(i=ctr;i>0&&lungimi[i].first>=3;i--)
        {
            if(!used[lungimi[i].second])
            {
                used[lungimi[i].second]=1;
                rez-=lungimi[i].first;
                j=vecini[lungimi[i].second].first;
                k=vecini[lungimi[i].second].second;
                while(j>0&&k<=ctr&&data[j].first==data[k].first)
                {
                    sj=data[j].second;
                    sk=data[k].second;
                    rez-=data[j].second;
                    rez-=data[k].second;
                    while(j>0&&data[vecini[j].first].first==data[j].first&&!used[vecini[j].first])
                    {
                        used[j]=1;
                        rez-=data[vecini[j].first].second;
                        sj+=data[vecini[j].first].second;
                        j=vecini[j].first;
                    }
                    while(k<=N&&data[vecini[k].second].first==data[k].first&&!used[vecini[k].second])
                        {
                            used[k]=1;
                            rez-=data[vecini[k].second].second;
                            sk+=data[vecini[k].second].second;
                            k=vecini[k].second;
                        }
                    if(sj+sk<3)
                        {                    rez+=data[j].second;
                    rez+=data[k].second;break;}
                    else
                        {used[j]=used[k]=1;j=vecini[j].first;k=vecini[k].second;}
                }
                vecini[j].second=k;
                vecini[k].first=j;
            }
        }
        fprintf(g,"%d\n",rez);
        for(i=1;i<=ctr;i++)
        {
            if(used[i]==0)
            {
                for(j=1;j<=data[i].second;j++)
                    fprintf(g,"%d\n",data[i].first);
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
