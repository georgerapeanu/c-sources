#include <iostream>
#include <cstring>
using namespace std;
string V[]={"","A","B","BOTH"};
int M,N;
int T[100005];
int viz[100005];
int dist[100005];
int ficycle(int &nod,int cul)
{
    dist[nod]=1;
    while(1)
    {
        viz[nod]=cul;
        if(!viz[T[nod]])
        {
            dist[T[nod]]=dist[nod]+1;
            nod=T[nod];
        }
        else if(viz[T[nod]]!=cul)return 0;
        else return dist[nod]-dist[T[nod]]+1;

    }
}
bool A()
{
    memset(viz,0,sizeof(viz));
    memset(dist,0,sizeof(dist));
    int cul=1;
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            int tmp=i;
            int len=ficycle(tmp,cul);cul++;
            if(len>2)return 0;
        }
        if(T[i]==i)return 0;
    }
    return 1;
}
bool B()
{
    memset(viz,0,sizeof(viz));
    memset(dist,0,sizeof(dist));
    int cul=1,nr=0,C,nod;
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            int tmp=i;
            int len=ficycle(tmp,cul);cul++;
            if(len){nr++;C=cul-1;nod=T[tmp];}
        }
    }
    if(nr>1)return 0;
    for(int i=1;i<=N;i++)
    {
        if(viz[T[T[i]]]==C&&viz[T[i]]!=C&&viz[i]!=C)return 0;
        if(viz[i]==C&&dist[i]<dist[nod]-1)return 0;
    }
    return 1;
}
int main()
{
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>N;
        for(int j=1;j<=N;j++)cin>>T[j];
        if(!A())
        {
            cout<<"B\n";
        }
        else if(!B())
        {
            cout<<"A\n";
        }
        else
        {
            cout<<"BOTH\n";
        }
    }
    return 0;
}
