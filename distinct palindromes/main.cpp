#include <iostream>
#include <cstring>
#define MOD 1000000007
using namespace std;
int T;
int N,M,K,S;
int dp1[3005][3005];
int dp2[3005][3005];
int main() {
    cin>>T;
    while(T--)
    {
       cin>>N>>M>>K>>S;
       int rez=0;
       memset(dp1,0,sizeof(dp1));
       memset(dp2,0,sizeof(dp2));
       dp1[0][0]=1;
      for(int i=1;i<=K;i++)
         for(int j=0;j<=N;j++)
            dp1[i][j]=(1LL*dp1[i-1][j+1]*(j+1)+(j ? 1LL*dp1[i-1][j-1]*(N-j+1):0LL))%MOD;
      dp2[0][0]=1;
      for(int i=1;i<=K;i++)
         for(int j=0;j<=M;j++)
            dp2[i][j]=(1LL*dp2[i-1][j+1]*(j+1)+(j ? 1LL*dp2[i-1][j-1]*(M-j+1):0LL))%MOD;
       for(int L=0;L<=N;L++)
         for(int C=0;C<=M;C++)
            if(L*M+C*N-2*L*C==S)
               rez=(rez+1LL*dp1[K][L]*dp2[K][C])%MOD;
      cout<<rez<<"\n";
    }
    return 0;
}
