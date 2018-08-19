#include <iostream>
#define BASE 31
#define MOD 1000000007
#define INV 129032259
using namespace std;
int pw[10005];
string a,c;
int dp[10005][5005];
struct hsh{
    int len=0;
    int cod=0;
    void addfront(char c)
    {
        cod=(cod+1LL*pw[len]*(c-'a'))%MOD;
        len++;
    }
    void addback(char c)
    {
        cod=(1LL*cod*BASE+c-'a')%MOD;
        len++;
    }
    void delfront(char c)
    {
        len--;
        cod=((cod-1LL*pw[len]*(c-'a'))%MOD+MOD)%MOD;
    }
    void delback(char c)
    {
        cod=((1LL*(cod-(c-'a'))*INV)%MOD+MOD)%MOD;
        len--;
    }
    bool operator ==(hsh &other)
    {
        return len==other.len&&cod==other.cod;
    }
}st,dr;
int V[10005];
int main()
{
    pw[0]=1;
    for(int i=1;i<=10000;i++)pw[i]=(1LL*pw[i-1]*BASE)%MOD;
    cin>>c;c=' '+c;
    for(int len=0;len<c.size();len++)
    {
        st.cod=st.len=0;
        dr.cod=dr.len=0;
        if(len%2==0)
        {
            for(int i=1;i<1+len/2;i++)st.addback(c[i]);
            for(int i=1+len/2+1;i<=1+len;i++)dr.addback(c[i]);
        }
        else
        {
            for(int i=1;i<=1+len/2;i++)st.addback(c[i]);
            for(int i=1+len/2+1;i<=1+len;i++)dr.addback(c[i]);
        }
        for(int i=1;i<c.size()-len;i++)
        {
            if(len==0)dp[i][i]=1;
            else
            {
                dp[i][i+len]=(dp[i+1][i+len-1]&&c[i]==c[i+len]);
                if(st==dr)
                {
                    if(len%2==0)dp[i][i+len]=max(dp[i][i+len],1+min(dp[i][i+len/2-1],dp[i+len/2+1][i+len]));
                    else        dp[i][i+len]=max(dp[i][i+len],1+min(dp[i][i+len/2],dp[i+len/2+1][i+len]));
                }
                if(len%2==1){st.delfront(c[i]);st.addback(c[i+1+len/2]);dr.delfront(c[i+1+len/2]);dr.addback(c[i+len+1]);}
                else        {st.delfront(c[i]);st.addback(c[i+len/2]);dr.delfront(c[i+len/2+1]);dr.addback(c[i+len+1]);}
            }
            V[1]++;
            V[dp[i][i+len]+1]--;
        }
    }
    for(int i=1;i<c.size();i++)
    {
        V[i]+=V[i-1];
        cout<<V[i]<<" ";
    }
    return 0;
}
