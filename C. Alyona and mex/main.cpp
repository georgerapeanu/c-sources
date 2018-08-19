#include <iostream>
#include <algorithm>
using namespace std;
int N,M,x,y,mex=(1<<30);
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>x>>y;
        mex=min(mex,y-x+1);
    }
    cout<<mex<<"\n";
    for(int i=0;i<N;i++)
        cout<<i%mex<<" ";
    return 0;
}
