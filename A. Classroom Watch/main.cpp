#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long N;
vector<long long> ans;
int S(long long N)
{
    if(!N)return 0;
    return N%10+S(N/10);
}
int main()
{
    cin>>N;
    for(int sum=0;sum<=81;sum++)
    {
        long long n=N-sum;
        if(S(n)==sum)
        {
            ans.push_back(n);
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    for(auto it:ans)cout<<it<<" ";
    return 0;
}
