#include <iostream>
#include <algorithm>
using namespace std;
int mex=1,i,N,V[100005];
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    sort(V+1,V+1+N);
    for(i=1;i<=N;i++)
    {
        if(mex<=V[i])
            mex++;
    }
    cout<<mex;
}
