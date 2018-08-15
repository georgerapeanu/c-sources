#include <iostream>
using namespace std;
int dp[1001][1001];
int l[1001],N,e,v;
int main()
{
    for(int i=0;i<=1000;i++)
    {
        dp[1][i]=i;
        dp[i][0]=0;
    }
    l[1]=1;
    for(int i=2;i<=1000;i++)
        {l[i]=l[i/2]+1;}
    for(int i=2;i<=10;i++)
    {
        for(int j=(1<<i);j<=1000;j++)
        {
            int minim=1001;
            for(int k=1;k<=j;k++)
            {
                int aux1,aux2;
                aux1 = l[k-1]<=i-1 ? l[k-1]:dp[i-1][k-1];
                aux2 = l[j-k]<=i ? l[j-k]:dp[i][j-k];
                int maxim=max(aux1,aux2);
                if(maxim<minim)
                    minim=maxim;
                else if(maxim>minim)
                    break;
            }
            dp[i][j]=minim+1;
        }
    }
    while(1)
    {
        cin>>e>>v;
        if(e==0&&v==0)
            break;
        cout<<(e>=l[v] ? l[v]:dp[e][v])<<"\n";
    }
    return 0;
}
