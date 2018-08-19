#include <iostream>
#define MOD 1000000007
using namespace std;
int N;
int x,rez;
int fr[1000005];
int V[1000005];
int pw2[1000005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++){cin>>x;fr[x]++;}
    pw2[0]=1;for(int i=1;i<=1000000;i++){pw2[i]=(pw2[i-1]<<1);if(pw2[i]>=MOD)pw2[i]-=MOD;}
    for(int i=1000000;i;i--)
    {
        int nr=0;
        for(int j=i;j<=1000000;j+=i){nr+=fr[j];V[i]-=V[j];if(V[i]<0)V[i]+=MOD;}
        V[i]=(V[i]+1LL*pw2[nr-1]*nr)%MOD;
    }
    for(int i=2;i<=1000000;i++)rez=(rez+1LL*i*V[i])%MOD;
    cout<<rez;
    return 0;
}
