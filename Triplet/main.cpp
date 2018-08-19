#include <iostream>
#include <cstdio>
using namespace std;
int N;
int main()
{
    freopen("triplet.in","r",stdin);
    freopen("triplet.out","w",stdout);
    cin>>N;
    cout<<(N%2==0)<<" ";
    N-=(N%2==0);
    cout<<(N+1)/2<<" "<<-((N+1)/2-1);
    return 0;
}
