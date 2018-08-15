#include <iostream>
#include <algorithm>
using namespace std;
int poz,mini=1<<30;
long long cost;
int N;
pair<int,int> V[100005];
int dist(int st,int dr)
{
    if(st>dr)swap(st,dr);
    return min(dr-st,N-dr+st);
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N);
    poz=V[1].second;
    for(int i=2;i<=N;i++)
    {
        cost+=dist(V[i].second,V[i-1].second);
        poz=V[i].second;
    }
    cout<<cost;
    return 0;
}
