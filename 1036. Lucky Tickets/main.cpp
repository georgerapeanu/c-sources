#include <iostream>
#include <vector>
#define ULL unsigned long long
#define B 10
using namespace std;
int N,S;
vector<int> dp[51][501];
vector <int> init(ULL val)
{
    vector <int> a;
    a.clear();
    while(val)
    {
        a.push_back(val%10);
        val/=10;
    }
    return a;
}
vector <int> add(vector <int> a,vector <int> b)
{
    int n=max(a.size(),b.size()),t=0;
    vector <int> c;
    c.clear();
    for(int i=0;i<n||t;i++)
    {
        c.push_back((a.size()<=i ? 0:a[i])+(b.size()<=i ? 0:b[i])+t);
        t=0;
        if(c[i]>=B)
        {
            c[i]-=B;
            t=1;
        }
    }
    return c;
}
vector <int> mul(vector <int> a,vector <int> b)
{
    vector <int> c(a.size()+b.size());
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
            c[i+j]+=a[i]*b[j];
    int t=0;
    for(int i=0;i<c.size()||t;i++)
    {
        if(i<c.size())
        {
            c[i]+=t;
            t=c[i]/B;
            c[i]%=B;
        }
        else
        {
            c.push_back(t%B);
            t/=B;
        }
    }
    int n=c.size()-1;
    while(n>0&&c[n]==0)
    {
        n--;
        c.pop_back();
    }
    return c;
}
int main()
{
    cin>>N>>S;
    if(S%2==1)
    {
        cout<<0;
        return 0;
    }
    S/=2;
    dp[0][0]=init(1);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=S&&j<=i*9;j++)
        {
            for(int k=0;k<=9&&k<=j;k++)
            {
                dp[i][j]=add(dp[i][j],dp[i-1][j-k]);
            }
        }
    }
    vector <int> rez;
    for(int i=0;i<=N;i++)
    {
        rez=add(rez,dp[i][S]);
    }
    rez=mul(rez,rez);
    int n=rez.size();
    for(int i=n-1;i>=0;i--)
        cout<<rez[i];
    if(!rez.size())
        cout<<0;
    return 0;
}
