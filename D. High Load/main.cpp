#include <iostream>
#include <cstdio>
#define inf 1<<30
using namespace std;
int N,K;
int dp[105][105];
void actual()
{
    if(N-K==1)
    {
        cout<<2<<"\n";
    }
    else if(N-K==2)
    {
        cout<<3<<"\n";
    }
    else
    {
        cout<<4<<"\n";
    }
}
int solve(int N,int K,bool afis)
{
    if(!afis)
    {
        if(N==2&&K==2)return 1;
        if(N==1&&K==1)return 0;
        if(N==K+1)
        {
            return 2;
        }
        if(N-K<=K)
        {
            if(N-K==2)return 2+solve(N-K,N-K,0);
            else return 2+solve(N-K,N-K-1,0);
        }
        else
        {
            return 2+solve(N-K,K,0);
        }
    }
    if(N==2&&K==2)
    {
        cout<<"1 2"<<"\n";return 0;
    }
    else if(N==1&&K==1)
    {
        return 0;
    }
    if(N==K+1)
    {
        for(int i=2;i<=N;i++)
            cout<<"1 "<<i<<"\n";
        return 0;
    }
    if(N-K<=K)
    {
        if(N-K==2)
        {
            solve(2,2,1);
            cout<<"1 3\n";
            for(int i=4;i<=N;i++)cout<<"2 "<<i<<"\n";
            return 0;
        }
        solve(N-K,N-K-1,1);
        int nodnou=N-K+1;
        int frunza=2;
        for(frunza=2;frunza<=N-K;frunza++)
        {
            cout<<frunza<<" "<<nodnou<<"\n";
            nodnou++;
        }
        while(nodnou<=N)
        {
            cout<<"2 "<<nodnou<<"\n";
            nodnou++;
        }
    }
    else
    {
        solve(N-K,K,1);
        for(int i=N-K+1;i<=N;i++)
        {
            cout<<i-K<<" "<<i<<"\n";
        }
        return 0;
    }
}
void tmp()
{
    dp[1][1]=0;
    dp[2][1]=inf;
    dp[2][2]=1;
    for(int i=3;i<=100;i++)
    {
        dp[i][1]=inf;
        for(int j=i;j<=100;j++)dp[i][j]=inf;
        for(int j=2;j<i;j++)
        {
            int rez=inf;
            for(int k=1;k<=i-j&&k<=j;k++)
                rez=min(rez,dp[i-j][k]);
            dp[i][j]=rez+2;
        }
    }
    for(int i=1;i<=100;i++,cout<<"\n")
    {
        for(int j=1;j<=i;j++)
            cout<<(dp[i][j]==(1<<30) ? -1:dp[i][j])<<" ";
    }
}
int main()
{
    //freopen("out","w",stdout);
    cin>>N>>K;
    cout<<solve(N,K,0)<<"\n";
    solve(N,K,1);
    return 0;
}
