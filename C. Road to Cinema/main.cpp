#include <iostream>
#include <algorithm>
#define MAXS 1000000005
#define inf 1000000005
using namespace std;
typedef struct{int cap,cost;} masina;
masina V[200005];
int loc[200005];
int N,K,S,T,maxdist,price=inf;
int okfuel(int fuel,int dist)
{
    int st=0,dr=dist;
    int mid,last=-1;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(2*(dist-mid)+mid<=T&&2*mid+dist-mid<=fuel)
        {
            last=mid;
            st=mid+1;
        }
        else if(2*mid+dist-mid<=fuel&&2*(dist-mid)+mid>T)
            st=mid+1;
        else
            dr=mid-1;
    }
    if(last!=-1)
        return 2*(dist-last)+last;
    return 0;
}
bool cmp(masina a,masina b)
{
    return a.cap<b.cap;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>K>>S>>T;
    for(int i=1;i<=N;i++)
        cin>>V[i].cost>>V[i].cap;
    for(int i=1;i<=K;i++)
    {
        cin>>loc[i];
        maxdist=loc[i]-loc[i-1];
    }
    sort(loc+1,loc+1+K);
    loc[K+1]=S;
    sort(V+1,V+1+N,cmp);
    int st=1,dr=N,mid,last=-1;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        int timp=0;
        for(int i=1;i<=K+1;i++)
        {
            int tmp=okfuel(V[mid].cap,loc[i]-loc[i-1]);
            if(!tmp)
            {
                timp=T+1;
                break;
            }
            timp+=tmp;
        }
        if(timp<=T)
        {
            last=mid;
            dr=mid-1;
        }
        else
            st=mid+1;
    }
    if(last==-1)
    {
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=N;i++)
    {
        if(V[i].cost<price&&V[i].cap>=V[last].cap)
        {
            price=V[i].cost;
        }
    }
    cout<<price;
    return 0;
}
