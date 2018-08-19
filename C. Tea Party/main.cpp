#include <iostream>
#include <algorithm>
#define x first
#define y second
using namespace std;
pair<int,int> V[105];
int R[105];
int poured=0;
int N,W;
int main()
{
    cin>>N>>W;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].x;V[i].y=i;
    }
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        poured=max(poured,V[i].x/2+V[i].x%2);
        R[V[i].y]=poured;
        W-=poured;
    }
    if(W>0){int ind=N;while(W>0){int m=min(W,V[ind].x-R[V[ind].y]);R[V[ind].y]+=m;W-=m;ind--;}}
    if(W<0)
    {cout<<-1;return 0;}
    for(int i=1;i<=N;i++)
        cout<<R[i]<<" ";
    return 0;
}
