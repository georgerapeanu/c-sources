#include <iostream>

using namespace std;
int f[100];
int N;
int main()
{
    cin>>N;
    f[1]=1;
    f[0]=1;
    for(int i=2;i<=N;i++)
    {
        for(int j=0;j<i;j++)
            f[i]+=f[j]*f[i-j-1];
        cout<<f[i]<<" ";
    }
    return 0;
}
