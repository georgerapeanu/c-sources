#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int N,K;
vector<int> P;
int fr[1000006];
bool B[1000006];
int rez[1000006];
int lg(long long N,int p)
{
    int rez=0;
    while(N>=p)
    {
        N/=p;
        rez++;
    }
    return rez;
}
int main() {
    cin>>N>>K;
    B[0]=B[1]=1;
    for(int i=2;i*i<=1000000;i++)
    {
        if(!B[i])
        {
            for(int j=i*i;j<=1000000;j+=i)
            {
                B[j]=1;
            }
        }
    }
    for(int i=1;i<=1000000;i++)if(!B[i])P.push_back(i);
    K=N*(N-1)/2-K;
    for(int i=1;i<=N;i++)rez[i]=P[i+1];
    int t=2;
    while(t*(t-1)/2<=K)t++;
    t--;
    if(t==1)t=0;
    for(int i=1;i<=t;i++)rez[i]*=2;
    for(int i=1;i<=K-t*(t-1)/2;i++)rez[i]*=3;
    rez[t+1]*=3;
    for(int i=1;i<=N;i++)cout<<rez[i]<<" ";
    return 0;
}
