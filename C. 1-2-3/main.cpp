#include <iostream>

using namespace std;
long long a,b;
long long K;
long long ciclu[1000];
long long len;
long long st;
long long viz[1000];
long long ha(long long a,long long b){return a*4+b;}
long long A[4][4];
long long B[4][4];
long long rezA,rezB;
bool bate(long long a,long long b)
{
    return a==b+1||(a==1&&b==3);
}
int main()
{
    cin>>K>>a>>b;
    for(long long i=1;i<=3;i++)for(long long j=1;j<=3;j++)cin>>A[i][j];
    for(long long i=1;i<=3;i++)for(long long j=1;j<=3;j++)cin>>B[i][j];
    while(!viz[ha(a,b)])
    {
        ciclu[++len]=ha(a,b);
        viz[ha(a,b)]=len;
        long long na,nb;
        na=A[a][b];
        nb=B[a][b];
        a=na;b=nb;
    }
    st=viz[ha(a,b)];
    for(long long i=1;i<min(0LL+st,K+1);i++)
    {
        rezA+=bate(ciclu[i]/4,ciclu[i]%4);
        rezB+=bate(ciclu[i]%4,ciclu[i]/4);
    }
    K=K-st+1;
    if(K>0)
    {
        for(long long i=st;i<=len;i++)
        {
            rezA+=(K/(len-st+1)+(K%(len-st+1)>=i-st+1))*bate(ciclu[i]/4,ciclu[i]%4);
            rezB+=(K/(len-st+1)+(K%(len-st+1)>=i-st+1))*bate(ciclu[i]%4,ciclu[i]/4);
        }
    }
    cout<<rezA<<" "<<rezB;
    return 0;
}
