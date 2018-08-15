#include <iostream>
#define MOD 1000000007
using namespace std;
int N;
string a,b;
int dp[60][4][4];
int rez;
void fix(int &val)
{
    if(val>=MOD)val-=MOD;
}
int main()
{
    cin>>N>>a>>b;
    a=" "+a;
    b=" "+b;
    if(a[1]==b[1])for(int j=1;j<4;j++)dp[1][j][j]=1;
    else          for(int j=1;j<4;j++)for(int k=1;k<4;k++)if(j!=k)dp[2][j][k]=1;
    for(int i=2+(a[1]!=b[1]);i<a.size();i++)
    {
        if(a[i]==b[i])
        {
            for(int j=1;j<4;j++)
            {
                for(int k=1;k<4;k++)
                {
                    if(k==j)continue;
                    for(int l=1;l<4;l++)
                    {
                        if(l==j)continue;
                        fix(dp[i][j][j]+=dp[i-1][k][l]);
                    }
                }
            }
        }
        else if(a[i-1]==a[i])
        {
            for(int j=1;j<4;j++)
            {
                for(int k=1;k<4;k++)
                {
                    if(j==k)continue;
                    for(int l=1;l<4;l++)
                    {
                        if(l==j)continue;
                        for(int m=1;m<4;m++)
                        {
                            if(m==k)continue;
                            fix(dp[i][j][k]+=dp[i-2][l][m]);
                        }
                    }
                }
            }
        }
    }
    for(int j=1;j<4;j++)for(int k=1;k<4;k++)fix(rez+=dp[N][j][k]);
    cout<<rez;
    return 0;
}
