#include <cstdio>
#include <vector>
#include <algorithm>
#define x first
#define ind second.second
#define tip second.first
#define zeros(x) (x&(x^(x-1)))
#define NMAX 1000001
using namespace std;
FILE *f=fopen("proc2.in","r");
FILE *g=fopen("proc2.out","w");
int N,M;
int S,D,lg;
int rez[100001];
int AIB[NMAX];
vector<pair<int,pair<int,int> > > E;
void update(int poz,int val)
{
    for(int i=poz;i<=N;i+=zeros(i))
        AIB[i]+=val;
}
int query(int poz)
{
    int suma=0;
    for(int i=poz;i;i-=zeros(i))
        suma+=AIB[i];
    return suma;
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&S,&D);
        E.push_back(make_pair(S,make_pair(1,i)));
        E.push_back(make_pair(S+D,make_pair(-1,i)));
    }
    int BN=N;
    lg=-1;
    while(BN)
    {
        lg++;
        BN/=2;
    }
    sort(E.begin(),E.end());
    for(auto it:E)
    {
        if(it.tip==-1)
        {
            update(rez[it.ind],-1);
        }
        else
        {
            int poz=0;
            for(int i=(1<<lg);i;i>>=1)
            {
                if(AIB[i+poz]==i)///poz+1....poz+i
                    poz+=i;
            }
            poz++;
            rez[it.ind]=poz;
            update(poz,1);
        }
    }
    for(int i=1;i<=M;i++)
        fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
