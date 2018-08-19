#include <iostream>
using namespace std;
unsigned char dp[901][8101][9];
int s1,s2,N;
int nrcf(unsigned char V[])
{
    int sum=0;
    for(int i=0;i<9;i++)
        sum+=V[i];
    return sum;
}
bool cmp(unsigned char a[],unsigned char b[],int cf)
{
    if(!nrcf(a))
        return 1;
    int cfa=nrcf(a);
    int cfb=nrcf(b);
    if(cfa!=cfb+1)
        return cfa>cfb;
    int tmp=0;
    while(a[tmp]==b[tmp]+(tmp==cf)&&tmp<9)
        tmp++;
    if(tmp==9)
        return 0;
    return a[tmp]<b[tmp]+(tmp==cf);
}
int main()
{
    for(int i=1;i<=900;i++)
    {
        for(int j=1;j<=8100;j++)
        {
            for(int k=1;k<=9&&i>=k&&j>=k*k;k++)
            {
                if((nrcf(dp[i-k][j-k*k])||(i==k&&j==k*k))&&nrcf(dp[i-k][j-k*k])<100&&cmp(dp[i][j],dp[i-k][j-k*k],k))
                {
                    for(int tmp=0;tmp<=8;tmp++)
                    {
                        dp[i][j][tmp]=dp[i-k][j-k*k][tmp];
                    }
                    dp[i][j][k-1]++;
                }
            }
        }
    }
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>s1>>s2;
        if(s1>900||s2>8100)
            cout<<"No solution\n";
        else
        {
            if(nrcf(dp[s1][s2])==0)
                cout<<"No solution\n";
            else
            {
                for(int j=0;j<9;j++)
                {
                    for(int k=1;k<=dp[s1][s2][j];k++)
                        cout<<j+1;
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}
