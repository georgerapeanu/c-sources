#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int N,M;
vector<pair<int,int> > G[5005];
long long  d[5005][2];
struct data
{
   bool p=0;
   int nod;
   long long cost;
   data()
   {
    ;
   }
   data(bool P,int NOD,long long COST)
   {
       p=P;
       nod=NOD;
       cost=COST;
   }
   bool operator <(const data &other)const
   {return cost>other.cost;}
};
priority_queue<data> H;
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)d[i][0]=d[i][1]=1LL<<60;
    for(int i=1;i<=M;i++)
    {
       int x,y,z;
       cin>>x>>y>>z;
       G[x].push_back({y,z});
       G[y].push_back({x,z});
    }
    d[1][0]=0;
    H.push(data(0,1,0));
    while(!H.empty())
    {
       data tmp=H.top();H.pop();
       if(d[tmp.nod][tmp.p]!=tmp.cost)continue;
       for(auto it:G[tmp.nod])
       {
          if(d[tmp.nod][tmp.p]>=it.second)
          {
             if(d[it.first][!tmp.p]>d[tmp.nod][tmp.p]+1)
             {
                d[it.first][!tmp.p]=d[tmp.nod][tmp.p]+1;
                H.push(data(!tmp.p,it.first,d[tmp.nod][tmp.p]+1));
             }
          }
          else
          {
            if(d[it.first][!tmp.p]>it.second+(it.second%2!=tmp.p)+1)
            {
               d[it.first][!tmp.p]=it.second+(it.second%2!=tmp.p)+1;
               H.push(data(!tmp.p,it.first,it.second+(it.second%2!=tmp.p)+1));
            }
          }
       }
    }
    long long rez=min(d[N][0],d[N][1]);
    if(rez!=1LL<<60)cout<<rez;
    else cout<<-1;
    return 0;
}
