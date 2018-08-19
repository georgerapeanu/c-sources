#include <iostream>

using namespace std;
class NoReplayPlaylist
{
public:
    const long long MOD=1000000007;
    long long lgpow(long long base,int exp)
    {
        long long p=1;
        while(exp)
        {
            if(exp&1)
                p=(p*base)%MOD;
            base=(base*base)%MOD;
            exp>>=1;
        }
        return p;
    }
    int f(int N,int M,int P)
    {
//        if(N==0) return 0;
//        if(N==M) return 1;
        long long rez=1;
        for(int i=N-M+1;i<=N;i++)
            rez=(rez*i)%MOD;
        rez=(rez*lgpow(N-M,P-M))%MOD;
        return rez;
    }
    int numPlaylists(int N,int M,int P)
    {
        int C[105][105];
        for(int i=0;i<=N;i++)
            C[i][0]=C[i][i]=1;
        for(int i=1;i<=N;i++)
            for(int j=1;j<i;j++)
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        long long rez;
        rez=f(N,M,P);
        long long scoef=0,coef=1;
        for(int i=N-1;i>=M;i--)
        {
            coef=C[N][i]-scoef;
            rez-=coef*f(i,M,P);
            rez%=MOD;
            scoef+=coef;
        }
        if(rez<0)
            rez+=MOD;
        return rez;
    }
};
///C(N,i)
///C(N,i-1)=C(N,i)*((N-i+1)/i)
int main()
{
    NoReplayPlaylist a;
    cout<<a.numPlaylists(3,0,3);
    return 0;
}

