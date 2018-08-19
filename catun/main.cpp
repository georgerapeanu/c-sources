#include <cstdio>
#include <queue>
#include <vector>
#include <fstream>
#define vecin first
#define cost second
#define dist first
#define nod second
using namespace std;
FILE *f=fopen("catun.in","r");
FILE *g=fopen("catun.out","w");
class cmp
{
    public:
    bool operator () (pair<long long,long long> a,pair<long long,long long> b)
    {
        return a>b;
    }
};
priority_queue <pair<long long,long long>,vector<pair<long long,long long> >,cmp> H;
long long N,M,K,a,b,c,i,j;
pair<long long,long long> D[36001];
long long k;
long long rez[36001];
vector <pair<long long,long long> > G[36001];
void dijkstra()
{
    while(!H.empty())
    {
        pair<long long,long long> x=H.top();
        H.pop();
        for(auto it:G[x.nod])
        {
            if(D[it.vecin].first>D[x.nod].first+it.cost||D[it.vecin].first==-1)
            {
                D[it.vecin].first=D[x.nod].first+it.cost;
                D[it.vecin].second=D[x.nod].second;
                H.push(make_pair(D[it.vecin].first,it.vecin));
            }
            else if(D[it.vecin].first==D[x.nod].first+it.cost&&D[it.vecin].second>D[x.nod].second)
            {
                D[it.vecin].second=D[x.nod].second;
                H.push(make_pair(D[it.vecin].first,it.vecin));
            }
        }
    }
}
int main()
{
    fscanf(f,"%lld%lld%lld",&N,&M,&K);
    for(j=1;j<=N;j++)
    {
        D[j].first=-1;
    }
    for(i=1;i<=K;i++)
        {fscanf(f,"%lld",&k);H.push(make_pair(0,k));D[k]=make_pair(0,k);}
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%lld %lld %lld",&a,&b,&c);
        G[a].push_back(make_pair(b,c));
        G[b].push_back(make_pair(a,c));
    }
    dijkstra();
    for(j=1;j<=N;j++)
        {
            if(D[j].second==j||D[j].first==-1)
                fprintf(g,"0 ");
            else
                fprintf(g,"%lld ",D[j].second);
        }
    fclose(f);
    fclose(g);
    return 0;
}
