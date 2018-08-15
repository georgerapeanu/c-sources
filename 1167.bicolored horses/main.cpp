#include <iostream>
#include <algorithm>
#define inf 250005
using namespace std;
int D[505][505],A[505],N[505];
int H,K,val;
int main()
{
    cin>>H>>K;
    for(int i=1;i<=H;i++)
    {
        cin>>val;
        N[i]=N[i-1];
        A[i]=A[i-1];
        if(val)
            N[i]++;
        else
            A[i]++;
        D[i][1]=A[i]*N[i];
        for(int j=2;j<=K&&j<=i;j++)
        {
            D[i][j]=inf;
            for(int grup_ult=i;grup_ult>=j;grup_ult--)
            {
                D[i][j]=min(D[i][j],D[grup_ult-1][j-1]+(A[i]-A[grup_ult-1])*(N[i]-N[grup_ult-1]));
            }
        }
    }
    cout<<D[H][K];
    return 0;
}
