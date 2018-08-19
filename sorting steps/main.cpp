#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int A[100005];
int rez=1;
vector<pair<int,int> > V;
int AIB[100005];
void u(int poz,int val)
{
    for(int i=poz;i<=N;i+=(-i)&i)
        AIB[i]+=val;
}
int q(int poz)
{
    int sum=0;
    for(;poz;poz-=(-poz)&poz)sum+=AIB[poz];
    return sum;
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        V.push_back(make_pair(A[i],i));
        u(i,1);
    }
    sort(V.begin(),V.end());
    int last=-1;
    for(int i=0;i<V.size();i++)
    {
        while(last<i||(last<V.size()&&V[last].first==V[last+1].first))
        {
            u(V[++last].second,-1);
        }
        if(i+1<=V[i].second)
        {
            rez=max(rez,V[i].second-i);
        }
        else
        {
            rez=max(1+q(i+1)-q(V[i].second),rez);
        }
    }
    cout<<rez;
    return 0;
}
