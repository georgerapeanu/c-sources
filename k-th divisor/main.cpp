#include <iostream>
#include <vector>
using namespace std;
long long N,K;
vector<long long> tmp;
int main()
{
    cin>>N>>K;
    for(long long i=1;i*i<=N;i++)
    {
        if(N%i==0)
        {
            K--;
            if(!K) {cout<<i;return 0;}
            if(i*i!=N)
                {tmp.push_back(N/i);}
        }
    }
    if(K>tmp.size()) {cout<<-1;return 0;}
    cout<<tmp[tmp.size()-K];
    return 0;
}
