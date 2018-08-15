#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
FILE *f=fopen("in","r");
FILE *g=fopen("out","w");
int cod[]={1,3,2,6,4,5};
int NR[]={1,2,1,2,1,2};
int V[7];
int N;
int nxt[1005];
int val[1005];
char ceva[]="ROYGBV";
struct cmp
{
    bool operator () (pair<int,int> a,pair<int,int> b)
    {
        if(a.first!=b.first)return a.first<b.first;
        if(NR[a.second]!=NR[b.second]) NR[a.second]>NR[b.second];
        return a.second<b.second;
    }
};
multiset<pair<int,int> ,cmp> H;
bool pot(int poz,int unde)
{
    int i=1;
    do
    {
        if(((cod[val[i]]&cod[poz])==0||val[i]==-1)&&((cod[poz]&cod[val[nxt[i]]])==0||val[nxt[i]]==-1))
        {
            nxt[unde]=nxt[i];
            nxt[i]=unde;
            val[unde]=poz;
            return 1;
        }
        i=nxt[i];
    }
    while(i!=1);
    return 0;
}
int main()
{
    int T;
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        fprintf(g,"Case #%d: ",i);
        fscanf(f,"%d",&N);
        H.clear();
        for(int i=0;i<6;i++)
            {fscanf(f,"%d",&V[i]);H.insert({V[i],i});}
        for(int i=1;i<=N;i++)
        {
            nxt[i]=1;
            val[i]=-1;
        }
        int nr=0;
        for(int i=1;i<=N;i++)
        {
            for(multiset<pair<int,int> >::reverse_iterator it=H.rbegin();it!=H.rend();it++)
            {
                int j=it->second;
                if(it->first&&pot(j,i))
                {
                    pair<int,int> tmp=*it;
                    multiset<pair<int,int> >::iterator t;
                    t=H.find(tmp);
                    H.erase(t);
                    tmp.first--;
                    H.insert(tmp);
                    nr++;
                    break;
                }
            }
        }
        if(nr!=N)fprintf(g,"IMPOSSIBLE\n");
        else
        {
            for(int i=1;i<=N;i++)
                fprintf(g,"%c",ceva[val[i]]);
            fprintf(g,"\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
