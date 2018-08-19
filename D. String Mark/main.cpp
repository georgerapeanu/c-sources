#include <iostream>
#define MOD 1000000007
using namespace std;
int fact[1000006];
int ifact[1000006];
int fr[280];
string a,b;
int add(int a,int b)
{
    a+=b;
    if(a>=MOD)
        a-=MOD;
    return a;
}
int scad(int a,int b)
{
    a-=b;
    if(a<0)
        a+=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=mult(p,b);
        b=mult(b,b);
        e>>=1;
    }
    return p;
}
int numUnique(int sum)
{
    int rez=fact[sum];
    for(int i='a';i<='z';i++)
    {
        rez=mult(rez,ifact[fr[i]]);
    }
    return rez;
}
int nrmod,len;
void increaseFreq(int i)
{
    fr[i]++;
    len++;
    nrmod=mult(nrmod,mult(len,mult(ifact[fr[i]],fact[fr[i]-1])));
}
void decreaseFreq(int i)
{
    nrmod=mult(nrmod,mult(fr[i],mult(fact[len-1],ifact[len])));
    len--;
    fr[i]--;
}
int cateMaiMici(string a,string b)///din literele lui a mai mici ca b
{
    int rez=0;
    for(int i='a';i<='z';i++)
    {
        fr[i]=0;
    }
    for(auto it:a)
    {
        fr[it]++;
    }
    len=a.size();
    nrmod=numUnique(len);
    for(int i=0;i<=(int)b.size();i++)
    {
        for(int j='a';j<b[i];j++)
        {
            if(fr[j])
            {
                decreaseFreq(j);
                rez=add(rez,nrmod);
                increaseFreq(j);
            }
        }
        if(i!=(int)b.size())
        {
            if(fr[b[i]]==0)
                break;
            decreaseFreq(b[i]);
        }
    }
    return rez;
}
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    fact[0]=1;
    for(int i=1;i<=1000000;i++)
    {
        fact[i]=mult(fact[i-1],i);
    }
    ifact[1000000]=lgpow(fact[1000000],MOD-2);
    for(int i=1000000-1;i>=0;i--)
    {
        ifact[i]=mult(ifact[i+1],i+1);
    }
    cin>>a>>b;
    cout<<scad(scad( cateMaiMici(a,b),cateMaiMici(a,a) ),1);
    return 0;
}
