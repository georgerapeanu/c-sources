#include <iostream>
#define inf 200000
using namespace std;
long long V[25],summax,indst,S[1<<25],val,rez;
long long D[1<<25];
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    for(int i=(1<<(N))-1;i>=0;i--)
    {
        int ci=i;
        int nr=0;
        while(ci%2==1)
        {
            ci/=2;
            nr++;
        }
        S[i]=S[i+(1<<nr)]+V[nr+1];
        D[i]=inf;
    }
    D[0]=inf;
    D[(1<<(N))-1]=0;
    for(int i=(1<<N)-2;i>=0;i--)
    {
        for(int j=1;j<=N;j++)
        {
            if((i&(1<<(j-1)))==0&&(i&(1<<(j%N)))==0&&(i&(1<<(j+1)%N))==0)
            {
                for(int k=7;k>0;k--)
                {
                    D[i]=min(D[i],D[i+(1<<(j-1))*(((1<<2)&k)!=0)+(1<<(j%N))*(((1<<1)&k)!=0)+(1<<((j+1)%N))*(((1<<0)&k)!=0)]+S[0]-S[i]);
                }
            }
        }
    }
    cout<<D[0];
    return 0;
}
