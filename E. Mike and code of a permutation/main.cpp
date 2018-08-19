#include <iostream>
#include <queue>
using namespace std;
int gr[500005];
queue<int> Q;
int P[500005];
int T[500005];
int N,nr;
int main()
{
    cin>>N;nr=N;
    for(int i=1;i<=N;i++)
    {
        cin>>T[i];
        if(T[i]==-1){P[i]=nr;nr--;}
        else gr[T[i]]++;
    }
    for(int i=1;i<=N;i++)
    {
        if(gr[i]==0)Q.push(i);
    }
    while(!Q.empty())
    {
        int x=Q.front();Q.pop();
        if(P[x])continue;
        if(!P[x])
        {
            ++P[0];
            P[x]=P[0];
        }
        gr[T[x]]--;
        if(!gr[T[x]])
            Q.push(T[x]);
    }
    for(int i=1;i<=N;i++)cout<<P[i]<<" ";
    return 0;
}
