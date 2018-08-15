#include <iostream>
#include <queue>
using namespace std;
int a,b,k,T;
int dp[30][11][10];
queue<int> Q;
#define inf 1<<30
int main()
{
    cin>>T;
    for(int i=1;i<=29;i++)
    {
        for(int j=2;j<=10;j++)
            for(int k=0;k<j;k++)
                dp[i][j][k]=dp[i-1][j][0]+dp[i-1][j][1]+dp[i-1][j][2]+dp[i-1][j][3]+dp[i-1][j][4]+dp[i-1][j][5]+dp[i-1][j][6]+dp[i-1][j][7]+dp[i-1][j][8]+dp[i-1][j][9];
    }
    while(T)
    {
        cin>>a>>b>>k;
        a--;
        int nr=0;
        int put=1;
        while(b)
        {
            for(int i=0;i<k;i++)
            {
                S[nr][i]+=(b/k+(i<=b%k))*put;
            }
            b/=k;
            put*=k;
            nr++;
        }
        int aux=nr;
        put=1;
        while(a)
        {
            for(int i=0;i<k;i++)
            {
                S[nr][i]-=(a/k+(i<=a%k))*put;
            }
            a/=k;
            put*=k;
            nr++;
        }
        int tmp=0;
        for(int i=aux;i>=0;i--)
        {
            int minim=inf;
            for(int j=0;j<k;j++)
                minim=min(S[i][j],minim);
            tmp=0;
            for(int j=0;j<k;j++)
            {
                tmp+=j*(S[i][j]-minim);
            }
            tmp%=k;
            Q.push(tmp);
        }
        while(!Q.empty()&&Q.front()==0)
            Q.pop();
        if(Q.empty())
            cout<<0;
        else
            while(!Q.empty())
            {
                cout<<Q.front();
                Q.pop();
            }
        cout<<"\n";
        T--;
    }
    return 0;
}
