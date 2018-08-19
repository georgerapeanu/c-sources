#include <iostream>
using namespace std;
long long D[100][2];
int N,K;
int main()
{
    cin>>N>>K;
    D[0][0]=1;
    for(int i=1;i<=N;i++)
    {
       D[i][0]=D[i-1][1];
       D[i][1]=D[i-1][0]*(K-1)+D[i-1][1]*(K-1);
    }
    cout<<D[N][0]+D[N][1];
    return 0;
}
