#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
long long N;
char K[65];
unsigned long long dp[65];
int main()
{
    cin>>N;
    cin.getline(K+1,65);
    cin.getline(K+1,65);
    int len=strlen(K+1);
    for(int i=1;i<=len;i++)
    {
        unsigned long long nr=0,p10=1;
        int j=i;
        dp[i]=(1LL<<62);
        while(nr<N&&j)
        {
            nr=nr+p10*(K[j]-'0');
            p10*=10;
            j--;
            if(i-j!=1&&nr<p10/10) continue;
            if(nr>=N) break;
            dp[i]=min(dp[i],dp[j]*N+nr);
        }
    }
    cout<<dp[len];
    return 0;
}
