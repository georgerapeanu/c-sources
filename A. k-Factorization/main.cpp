#include <iostream>
#include <vector>
using namespace std;
vector<int> D;
int N,K;
int main()
{
    cin>>N>>K;
    for(int i=2;i*i<=N;i++)
    {
        while(N%i==0)
        {
            D.push_back(i);
            N/=i;
        }
    }
    if(N!=1)D.push_back(N);
    if(D.size()<K)cout<<-1;
    else
    {
        while(D.size()>K)
        {
            int a=D.back();
            D.pop_back();
            D.back()*=a;
        }
        for(auto it:D)
            cout<<it<<" ";
    }
    return 0;
}
