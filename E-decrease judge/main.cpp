#include <iostream>

using namespace std;
long long maxa=(1e16)+1000;
long long V[55];
long long K;
long long T[55];
long long baga[55];
long long maxop(int N,int st)
{
    long long nr=0;
    bool ok;
    for(int i=1;i<=N;i++)baga[i]=0;
    for(int i=1;i<st;i++)
        V[i]=T[i];
    for(int i=st;i<=N;i++)V[i]=maxa;
    do
    {
        ok=0;
        for(int i=1;i<=N;i++)
        {
            V[i]+=baga[i];
            if(V[i]>=N)
            {
                nr+=V[i]/N;ok=1;
            }
        }
        for(int i=1;i<=N;i++)
        {
            baga[i]=0;
            for(int j=1;j<=N;j++)
            {
                if(i!=j)
                {
                    baga[i]+=V[j]/N;
                }
            }
        }
        for(int i=1;i<=N;i++)
        {
            V[i]%=N;
        }
    }
    while(ok);
    return nr;
}
int main()
{
    cin>>K;
    for(int i=1;i<=K;i++)cin>>T[i];
    cout<<maxop(K,K+1);
    return 0;
}
