#include <iostream>
using namespace std;
long long N,M[7][50],i;
int main()
{
    cin>>N;
    M[1][2]=M[2][2]=M[5][2]=M[6][2]=1;
    for(i=3;i<=N;i++)
    {
        M[1][i]=M[3][i-1]+M[5][i-1];
        M[2][i]=M[3][i-1]+M[5][i-1];
        M[3][i]=M[6][i-1];
        M[4][i]=M[1][i-1];
        M[5][i]=M[2][i-1]+M[4][i-1];
        M[6][i]=M[2][i-1]+M[4][i-1];
    }
    if(N>=2)
    cout<<M[2][N]+M[3][N]+M[4][N]+M[5][N];
    else
        cout<<2;
    return 0;
}
///alb albastru -1
///alb rosu -2
///albastru alb -3
///albastru rosu-4
///rosu alb-5
///rosu albastru-6
