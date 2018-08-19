#include <iostream>
#define MOD 1000000009
using namespace std;
bool E[1000];
int DP[10005][10][10],rez,N;
int main()
{
    E[0]=E[1]=1;
    for(int i=2;i*i<1000;i++)
    {
        if(!E[i])
        {
            for(int j=i*i;j<=1000;j+=i)
                E[j]=1;
        }
    }
    cin>>N;
    for(int i=1;i<=9;i++)
        for(int j=0;j<=9;j++)
                DP[2][i][j]=1;
    for(int i=3;i<=N;i++)
    {
        for(int j=0;j<=9;j++)
        {
            for(int k=0;k<=9;k++)
            {
                for(int l=1;l<=9;l++)
                {
                    if(!E[l*100+j*10+k])
                    {
                        DP[i][j][k]=(DP[i][j][k]+DP[i-1][l][j])%MOD;
                    }
                }
            }
        }
    }
    for(int i=0;i<=9;i++)
        for(int j=0;j<=9;j++)
        {
            rez+=DP[N][i][j];
            rez%=MOD;
        }
    cout<<rez;
    return 0;
}
