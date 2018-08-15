#include <iostream>
#include <cmath>
#include <cstring>
#define EPS (1e-11)
using namespace std;
long double dp[1005][1005];
struct TheTicketsDivOne
{
    double find(int N,int M)
    {
        dp[1][1]=1;
        for(int i=2;i<=N;i++)
        {
            long double frac=pow((long double)3/6,i);
            long double ceva=0;
            for(int j=2;j<=i;j++)
                ceva=(ceva*(long double)3/6+(long double)2/6*dp[i-1][j-1]);
            dp[i][1]=((long double)3/6*ceva+(long double)1/6)/(1-frac);
            for(int j=2;j<=i;j++)
            {
                dp[i][j]=(((long double)2/6)*dp[i-1][j-1]+((long double)3/6)*dp[i][j-1]);
            }
        }
        return dp[N][M];
    }
};
TheTicketsDivOne a;
int main()
{
    cout<<a.find(2,2);
    //cerr<<tmp(3,3,0.338624338624)<<"\n";
   // cerr<<tmp(3,3,0.308624338624);
}
