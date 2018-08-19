#include <iostream>
#include <map>
using namespace std;
long long rez,T,nr;
map<long long,long long> S,D;
map<long long,long long> :: iterator dr,tmp;
long long V[40];
int N;
int main()
{
    cin>>N>>T;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=0;i<(1<<(N>>1));i++)
    {
        long long sum=0;
        for(int j=0;j<(N>>1);j++)
            sum+=((i>>j)&1)*V[j+1];
        S[sum]++;
    }
    for(int i=0;i<(1<<(N-N/2));i++)
    {
        long long sum=0;
        for(int j=0;j<N-N/2;j++)
        {
            sum+=((i>>j)&1)*V[N/2+1+j];
        }
        D[sum]++;
    }
    dr=D.end();dr--;
    tmp=D.begin();tmp--;
    for(auto it:S)
    {
        while(dr!=tmp&&it.first+dr->first>=T)
        {
            nr+=dr->second;
            dr--;
        }
        rez+=1LL*nr*it.second;
    }
    cout<<rez;
    return 0;
}
