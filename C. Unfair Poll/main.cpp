#include <iostream>
#include <vector>
#include <map>
using namespace std;
int N,M,X,Y;
long long K;
long long tmp,rest,a,b=(1LL<<62),c;
bool ok;
vector<pair<int,int> > V;
map<pair<int,int>,long long> frecv;
int main()
{
    cin>>N>>M>>K>>X>>Y;
    for(int i=1;i<=N;i++) for(int j=1;j<=M;j++) V.push_back(make_pair(i,j));
    for(int i=N-1;i>1;i--) for(int j=1;j<=M;j++) V.push_back(make_pair(i,j));
    long long len=V.size();
    tmp=K/len;
    rest=K%len;
    for(int i=0;i<len;i++)
        frecv[V[i]]+=tmp+(rest>i);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            pair<int,int> p=make_pair(i,j);
            if(p==make_pair(X,Y)) c=frecv[p];
            a=max(a,frecv[p]);
            b=min(b,frecv[p]);
        }
    }
    cout<<a<<" "<<b<<" "<<c;
    return 0;
}
