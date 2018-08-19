#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int N,Z,W;
int V[2005];
int main()
{
    cin>>N>>Z>>W;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    cout<<max(abs(W-V[N]),(N>1 ? abs(V[N-1]-V[N]):0));
    return 0;
}
