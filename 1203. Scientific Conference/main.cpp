#include <iostream>
#include <algorithm>
using namespace std;
int N,i,ult=-2,nr;
pair<int,int> V[100005];
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
        cin>>V[i].second>>V[i].first;
    sort(V+1,V+1+N);
    for(i=1;i<=N;i++)
    {
        if(V[i].second-ult>=1)
        {
            ult=V[i].first;
            nr++;
        }
    }
    cout<<nr;
    return 0;
}
