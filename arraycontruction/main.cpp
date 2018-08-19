#include <cmath>
#include <cstdio>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
int dp[51][201][2001];
int N,S,K,Q;
stack<int> ST;
int main() {
    cin>>Q;
    N=50;S=200;K=2000;
    for(int i=0;i<=S;i++)for(int j=0;j<=K;j++) {dp[1][i][j]=-1;dp[0][i][j]=201;}
    for(int i=0;i<=S;i++) dp[1][i][0]=i;
    for(int i=2;i<=N;i++)
    {
        for(int j=0;j<=S;j++)
        {
            for(int k=0;k<=K;k++)
            {
                dp[i][j][k]=-1;
                for(int nr=0;nr<=j/i;nr++)
                    if(j-nr>=0&&k+nr*(i-1)-(j-nr)<=K&&k+nr*(i-1)-(j-nr)>=0&&dp[i-1][j-nr][k+nr*(i-1)-(j-nr)]>=nr)
                        dp[i][j][k]=nr;
            }
        }
    }
    while(Q)
    {
        Q--;
        cin>>N>>S>>K;
        int i,j,k;
        i=N;j=S;k=K;
        if(dp[i][j][k]==-1){cout<<"-1\n";continue;}
        int nr=0;
        while(i)
        {
            while(!(j-nr>=0&&k+nr*(i-1)-(j-nr)<=K&&k+nr*(i-1)-(j-nr)>=0&&dp[i-1][j-nr][k+nr*(i-1)-(j-nr)]>=nr))
                nr++;
            int nj,nk;
            cout<<nr<<" ";
            nj=j-nr;
            nk=k+nr*(i-1)-(j-nr);
            i--;j=nj;k=nk;
        }
        cout<<"\n";
    }
    return 0;
}
