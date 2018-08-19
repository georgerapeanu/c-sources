#include <iostream>
using namespace std;
int N,X,i,a;
int main()
{
    cin>>N>>X;
    for(i=1;i<=N;i++)
    {
        cin>>a;
        if(a!=X)
            cout<<a<<" ";
    }
    return 0;
}
