#include <iostream>
#include <algorithm>
#include <vector>
#define ULL unsigned long long
#define B 10
using namespace std;
ULL N,M,K;
ULL rez[3][3],m[3][3],fval[3];
ULL fmod(vector <int> a)
{
    ULL rest=0;
    for(int i=a.size()-1;i>=0;i--)
    {
        rest=(rest*B+a[i])%M;
    }
    return rest;
}
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
    return c;
}
void inm(ULL a[3][3],ULL b[3][3])
{
    ULL rez[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            vector <int> aux=add(add(mul(init(a[i][0]),init(b[0][j])),mul(init(a[i][1]),init(b[1][j]))),mul(init(a[i][2]),init(b[2][j])));
            rez[i][j]=fmod(aux);
        }
    }
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            a[i][j]=rez[i][j];
}
void put(ULL N)
{
    while(N)
    {
        if(N&1)
        {
            inm(rez,m);

        }
        inm(m,m);
        N>>=1;
    }
}
int main()
{
    cin>>N>>K>>M;
    rez[0][0]=rez[1][1]=rez[2][2]=1;
    m[0][1]=1;
    m[1][2]=1;
    m[2][0]=M+1-(K%M);
    m[2][2]=K;
    fval[0]=1;
    fval[1]=K-1;
    vector <int> aux=mul(init(K-1),init(K));
    fval[2]=fmod(aux);
    put(N-2);
    if(N<=2)
        cout<<fval[N];
    else
    {
        vector <int> aux=add(add(mul(init(fval[0]),init(rez[2][0])),mul(init(fval[1]),init(rez[2][1]))),mul(init(fval[2]),init(rez[2][2])));
        cout<<fmod(aux);
    }
}
///f(i)=f(i-1)*k-f(i-3)*(K-1)
///toate variantele -
///a1a2a3a4.....ai-3ai-2ai-1ai
///                  !=0 0  0
