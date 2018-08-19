#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int T[500005];
char C[500005];
int N;
int id=0;
int nxt[500005];
int ant[500005];
pair<int,int> V[500005];
int mx=1;
int main()
{
    cin.getline(C+1,500005);
    N=strlen(C+1);N-=(C[N]=='\n');
    T[1]=N;
    id=0;
    for(int i=2;i<=N;i++)
    {
        T[i]=0;
        if(id+T[id]>i)
            T[i]=min(T[i-id+1],id+T[id]-i);
        while(C[T[i]+1]==C[i+T[i]])
            T[i]++;
        if(id+T[id]<i+T[i])id=i;
    }
    T[N+1]=N;
    for(int i=1;i<=N+1;i++)
        {
            V[i]=make_pair(T[i],i);
            ant[i]=i-1;
            nxt[i]=i+1;
        }
    sort(V+1,V+1+N);
    int ind=1;
    for(int l=1;l<=N;l++)
    {
        while(V[ind].first<l)
        {
            int a,b;
            a=ant[V[ind].second];
            b=nxt[V[ind].second];
            nxt[a]=b;
            ant[b]=a;
            nxt[V[ind].second]=ant[V[ind].second]=0;
            ind++;
            mx=max(mx,b-a);
        }
        if(mx<=l){cout<<l;return 0;}
    }
    return 0;
}
