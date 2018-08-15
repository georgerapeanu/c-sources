#include <iostream>
#include <set>
using namespace std;
int N,M,val;
int P[200005];
int A[200005];
int B[200005];
set<pair<int,int> >S[4];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)cin>>P[i];
    for(int i=1;i<=N;i++)cin>>A[i];
    for(int i=1;i<=N;i++)cin>>B[i];
    for(int i=1;i<=N;i++)
    {
        S[A[i]].insert({P[i],i});
        S[B[i]].insert({P[i],i});
    }
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>val;
        if(S[val].empty())
        {
            cout<<-1<<" ";
        }
        else
        {
            int ind=S[val].begin()->second;
            int cost=S[val].begin()->first;
            S[1].erase({cost,ind});
            S[2].erase({cost,ind});
            S[3].erase({cost,ind});
            cout<<cost<<" ";
        }
    }

    return 0;
}
