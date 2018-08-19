#include <cmath>
#include <cstdio>
#include <bitset>
#include <vector>
#include <iostream>
#include <algorithm>
#define PMAX 1500
using namespace std;
bitset<PMAX> E;
long long DP[19][170][PMAX];///cate numere de lungime i au suma cifrelor j si suma patratelor cifrelor k
long long ival;
bool ok(long long val)
{
    int a,b;
    a=b=0;
    while(val)
    {
        a+=val%10;
        b+=(val%10)*(val%10);
        val/=10;
    }
    if(E[a]||E[b]) return 0;
    return 1;
}
long long q(long long val)
{
    vector<int> digits;
    while(val)
    {
        digits.push_back(val%10);
        val/=10;
    }
    int s1,s2;s1=s2=0;
    long long rez=0;
    for(int i=digits.size()-1;i>=0;i--)
    {
        for(int l=0;l<digits[i];l++)
        {
            for(int j=0;j<=9*i;j++)
            {
                for(int k=0;k<=i*9*9;k++)
                {
                    if(DP[i][j][k]&&(!E[j+l+s1])&&(!E[k+l*l+s2]))
                        rez+=DP[i][j][k];
                }
            }
        }
        s1+=digits[i];
        s2+=digits[i]*digits[i];
    }
    rez+=(!E[s1]&&!E[s2]);
    return rez;
}
int main() {
    E[0]=E[1]=1;
  ///  freopen("1.in","r",stdin);
   /// freopen("1.out","w",stdout);
    for(int i=2;i*i<PMAX;i++)
    {
        if(!E[i])
        {
            for(int j=i*i;j<PMAX;j+=i)
                E[j]=1;
        }
    }
    DP[0][0][0]=1;
    for(int i=1;i<=18;i++)
    {
        for(int s=0;s<=9*i;s++)
        {
            for(int k=0;k<=9*9*i;k++)
            {
                for(int cf=0;cf<=9&&k-cf*cf>=0&&s-cf>=0;cf++)
                    DP[i][s][k]+=DP[i-1][s-cf][k-cf*cf];
            }
        }
    }
    int T;
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        long long a,b;
        cin>>a>>b;
        cout<<q(b)-q(a-1)<<"\n";
    }
    return 0;
}
