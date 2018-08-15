#include <iostream>
#include <algorithm>
using namespace std;
int A,B,C,D,E,F;
int a,b;
bool dp[3005][3005];
bool verif(int a,int b)
{
    return (a*E>=b*100)&&a+b<=F;
}
int main()
{
    cin>>A>>B>>C>>D>>E>>F;
    int dx[]={100*A,100*B,0};
    int dy[]={C,D,0};
    dp[0][0]=1;
    a=100*A;
    for(int i=0;i<=F;i++)
    {
        for(int j=0;j<=F-i;j++)
        {
            if(!verif(i,j))continue;
            for(int k=0;k<3;k++)
            {
                for(int l=0;l<3;l++)
                {
                    if(i>=dx[k]&&j>=dy[l])dp[i][j]|=dp[i-dx[k]][j-dy[l]];
                }
            }
            if(dp[i][j]&&j)
            {
                if(b*i<=j*a)
                {
                    a=i;
                    b=j;
                }
            }
        }
    }
    cout<<a+b<<" "<<b;
    return 0;
}
