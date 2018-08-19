#include<iostream>
#define MOD 1000000007
using namespace std;
int lgpow(int b,int e)
{
	int p=1;
	while(e)
	{
		if(e&1)p=(1LL*b*p)%MOD;
		b=(1LL*b*b)%MOD;
		e>>=1;
	}
	return p;
}
int fact[105],inv[105];
int C(int N,int M)
{
	if(M>N)return 1;
	return (1LL*((1LL*fact[N]*inv[M])%MOD)*inv[N-M])%MOD;
}
int init()
{
	fact[0]=inv[0]=1;
	for(int i=1;i<=104;i++)fact[i]=(1LL*i*fact[i-1])%MOD;
	inv[104]=lgpow(fact[104],MOD-2);
	for(int i=103;i;i--)inv[i]=(1LL*inv[i+1]*(i+1))%MOD;
}
struct DerangementsDiv2
{
	int count(int n,int m)
	{
		init();
		int rez=0;
		for(int i=0;i<=m;i++)
		{
			rez=(rez+1LL*(i%2==0 ? 1:-1)*fact[n+m-i]*C(m,i))%MOD;
		}
		return rez;
	}
};
