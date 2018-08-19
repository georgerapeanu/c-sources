#include <iostream>
#define inf 60005
using namespace std;
int D[60005];
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        D[i]=inf;
        for(int l=1;l*l<=i;l++)
            D[i]=min(D[i],D[i-l*l]+1);
    }
    cout<<D[N];
    return 0;
}
