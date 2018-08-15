#include <iostream>
#include <stack>
using namespace std;
int val[505][505];
int dp[505][505];
int ant[505][505];
int N,K,rez;
stack <int> st;
int main()
{
    cin>>N>>K;
    for(int i=1;i<N;i++)
    {
        for(int j=i+1;j<=N;j++)
            cin>>val[i][j];
        for(int j=N;j>i;j--)
            val[i][j]+=val[i][j+1];
    }
    dp[0][K]=-1;///dp[i][j]
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<=K,j<=i;j++)
        {
            dp[i][j]=-1;
            int tmp=val[i][i+1];
            for(int k=i-1;k>=j-1;k--)
            {
                if(dp[k][j-1]+tmp>dp[i][j])
                {
                    dp[i][j]=dp[k][j-1]+tmp;
                    ant[i][j]=k;
                }
                tmp+=val[k][i+1];
            }
        }
    }
    for(int i=N-1;i>=K;i--)
        if(dp[i][K]>dp[rez][K])
            rez=i;
    cout<<dp[rez][K]<<"\n";
    while(K)
    {
        st.push(rez);
        rez=ant[rez][K];
        K--;
    }
    while(!st.empty())
    {
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}
