#include <iostream>
#include <map>
using namespace std;
map<int,int> M;
int N,K;
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++){int val;cin>>val;M[val]++;}
    for(auto it:M)if(it.second%K!=0)cout<<it.first;
    return 0;
}
