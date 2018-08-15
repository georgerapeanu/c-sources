#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
vector<string> V;
int N,M,K,rez;
bool ok[1000006];
struct data
{
   int cost,costb;
   int st,dr;
   bool operator < (const data &other)const
   {
      return cost-costb<other.cost-other.costb;
   }
};
int get(int i,int j,char a)
{
    return (V[i][j]!=a)+(V[N-i+1][j]!=a)+(V[i][M-j+1]!=a)+(V[N-i+1][M-j+1]!=a);
}
vector<data> oau;
int main() {
    cin>>N>>M>>K;
    V.resize(N+1);
    for(int i=1;i<=N;i++)
    {
       cin>>V[i];
       V[i]=" "+V[i];
    }
    for(int i=1;i<=M/2;i++)
    {
         data tmp;tmp.st=i;tmp.dr=M-i+1;tmp.cost=0;
         tmp.costb=0;
         for(int j=1;j<=N/2;j++)
         {
            int tmpcost=0;
            tmpcost=min(min(get(j,i,V[j][i]),get(j,i,V[N-j+1][i])),min(get(j,i,V[j][M-i+1]),get(j,i,V[N-j+1][M-i+1])));
            tmp.cost+=tmpcost;
         }
         if(N%2!=0)
         {
            tmp.cost+=(V[N/2+1][i]!=V[N/2+1][M-i+1]);
         }
         for(int j=1;j<=N;j++)tmp.costb+=(V[j][i]!=V[j][M-i+1]);
         oau.push_back(tmp);
    }
    sort(oau.begin(),oau.end());
    if(K%2==0)
    {
       for(int i=0;i<K/2;i++)
       {
          ok[oau[i].st]=1;
          ok[oau[i].dr]=1;
          rez+=oau[i].cost;
       }
       for(int i=1;i<=N;i++)
       {
          for(int st=1,dr=M;st<dr;st++,dr--)
          {
             rez+=(!ok[st]&&!ok[dr]&&V[i][st]!=V[i][dr]);
          }
       }
    }
    else
    {
       int tmpreza=0;
       int tmprezb=0;
       if(K/2+1<=oau.size())
       {
          for(int i=0;i<K/2+1;i++)
          {
             ok[oau[i].st]=1;
             ok[oau[i].dr]=1;
             tmpreza+=oau[i].cost;
          }
          for(int i=1;i<=N;i++)
          {
             for(int st=1,dr=M;st<dr;st++,dr--)
             {
                tmpreza+=(!ok[st]&&!ok[dr]&&V[i][st]!=V[i][dr]);
             }
          }
       }
       else tmpreza=1<<20;
       if(M%2==0)tmprezb=1<<20;
       else
       {
          memset(ok,0,sizeof(ok));
          for(int st=1,dr=N;st<dr;st++,dr--)tmprezb+=(V[st][M/2+1]!=V[dr][M/2+1]);
          K--;
         for(int i=0;i<K/2;i++)
          {
             ok[oau[i].st]=1;
             ok[oau[i].dr]=1;
             tmprezb+=oau[i].cost;
          }
          for(int i=1;i<=N;i++)
          {
             for(int st=1,dr=M;st<dr;st++,dr--)
             {
                tmprezb+=(!ok[st]&&!ok[dr]&&V[i][st]!=V[i][dr]);
             }
          }
       }
       rez+=min(tmpreza,tmprezb);
    }
    cout<<rez;
    return 0;
}
