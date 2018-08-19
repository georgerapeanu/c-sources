#include <iostream>
#include <vector>
#define BASE 10000
#define pb push_back
using namespace std;
vector<int> dp[31][31][31][3];///dp[a1][a2][a3][j] cate moduri de a parcurge a1 orase de pe insula 3,a2 orase de pe 1,a3 de p2 2
///are sens,deoarece eu ma refer la insule ca si restul numerelor de pe ele la imparitirea cu 3
/// si pentru un motiv dubios,eu le-am notat de la dreapta la stanga:
/*
    6 5 4
    3 2 1
*/
int N;
vector<int> adun(vector<int> a,vector<int> b)
{
    int n=a.size();
    int m=b.size();
    int t=0;
    int i;
    vector<int> c;c.clear();
    for(int i=0;i<n||i<m||t;i++)
    {
        c.pb(t+(i<n ? a[i]:0)+(i<m ? b[i]:0));
        t=c[i]/BASE;
        c[i]%=BASE;
    }
    return c;
}
vector<int> mul(vector<int> a,int val)
{
    int n=a.size();
    int t=0;
    vector<int> c;c.clear();
    for(int i=0;i<n||t;i++)
    {
        c.pb(t+(i<n ? a[i]:0)*val);
        t=c[i]/BASE;
        c[i]%=BASE;
    }
    return c;
}
int main()
{
    dp[0][1][0][1].pb(1);
    int a[]={0,0,0,0,0};
    cin>>N;
    for(a[0]=0;a[0]<=N;a[0]++)
    {
        for(a[1]=1;a[1]<=N;a[1]++)
        {
            for(a[2]=0;a[2]<=N;a[2]++)
            {
                for(int j=0;j<3;j++)
                {
                    if(a[j])
                    {
                        ///dp[a[0]][a[1]][a[2]][j]+=dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][0]*(j!=0)*(N-a[j]+1)+dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][1]*(j!=1)*(N-a[j]+1)+dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][2]*(j!=2)*(N-a[j]+1);
                        vector<int> A;A.clear();
                        A.pb(0);
                        if(j!=0) A=adun(A,dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][0]);
                        if(j!=1) A=adun(A,dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][1]);
                        if(j!=2) A=adun(A,dp[a[0]-(j==0)][a[1]-(j==1)][a[2]-(j==2)][2]);
                        A=mul(A,N-a[j]+1);
                        dp[a[0]][a[1]][a[2]][j]=adun(dp[a[0]][a[1]][a[2]][j],A);
                    }
                }
            }
        }
    }
   for(vector<int> ::reverse_iterator it=dp[N][N][N][0].rbegin();it!=dp[N][N][N][0].rend();it++) ///pentru ca dp[N][N][N][0]=dp[N][N][N][2],deci (dp[N][N][N][0]+dp[N][N][N][2])/2=dp[N][N][N][0]
    {
        if(it!=dp[N][N][N][0].rbegin())
        {
            int cb=BASE/10;
            while(*it<cb)
            {
                if(*it==0&&cb==1) break;
                cout<<"0";
                cb/=10;
            }
        }
        cout<<*it;
    }
    return 0;
}
