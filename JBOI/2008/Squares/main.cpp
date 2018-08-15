#include <iostream>

using namespace std;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int nr(int a,int b)
{
    return a+b-gcd(a,b);
}
int tmp()
{
    int rez[1005];
    //memset(rez,0,sizeof(rez));
    for(int i=1;i<=1000;i++)
        for(int j=i;j<=1000;j++)
            if(nr(i,j)<=1000)
                rez[nr(i,j)]++;
    for(int i=1;i<=100;i++)cout<<rez[i]<<" ";
}
int N;
int rez;
int E[1000006];
int main()
{
    cin>>N;
    for(int i=2;i<=N+1;i++)
    {
        E[i]+=i/2;
        for(int j=i+i;j<=N+1;j+=i)
            E[j]-=E[i];
    }
    for(int j=1;j<=N;j++)
    {
        if(N%j==0)
        {
           rez+=E[N/j+1];
        }
    }
    cout<<rez;
    return 0;
}
