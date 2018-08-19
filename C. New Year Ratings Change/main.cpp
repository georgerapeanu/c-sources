#include <iostream>
#include <algorithm>
using namespace std;
pair<int,int> V[300005];
int ind,N;
int rez[300005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N);
    ind=1;
    for(int i=1;i<=N;i++)
    {
        ind=max(V[i].first,ind);
        rez[V[i].second]=ind;
        ind++;
    }
    for(int i=1;i<=N;i++)
        cout<<rez[i]<<" ";
    return 0;
}
