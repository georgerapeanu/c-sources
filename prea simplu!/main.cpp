#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
FILE *f=fopen("preasimplu.in","r");
FILE *g=fopen("preasimplu.out","w");
int MOD;
int phi;
int F[20];
int NR;
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1) p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
void INIT()
    {
        int tmp=MOD;
        phi=MOD;
        NR=0;
        memset(F,0,sizeof(F));
        for(int i=2;i*i<=tmp;i++)
        {
            if(tmp%i==0)
            {
                F[++NR]=i;
                phi=(phi/i)*(i-1);
                while(tmp%i==0) tmp/=i;
            }
        }
        if(tmp>1)
        {
            F[++NR]=tmp;
            phi=(phi/tmp)*(tmp-1);
        }
    }
struct DA
{
    int val;
    int fact[20];
    DA()
    {
        val=1;
        memset(fact,0,sizeof(fact));
    }
    DA(int nr)
    {
        memset(fact,0,sizeof(fact));
        val=nr;
        for(int i=1;i<=NR;i++)
        {
            while(val%F[i]==0)
            {
                fact[i]++;val/=F[i];
            }
        }
    }
    DA operator *(DA a)
    {
        DA ans;
        for(int i=1;i<=NR;i++)
            ans.fact[i]=fact[i]+a.fact[i];
        ans.val=(1LL*val*a.val)%MOD;
        return ans;
    }
    DA operator /(DA a)
    {
        DA ans;
        for(int i=1;i<=NR;i++)
            ans.fact[i]=fact[i]-a.fact[i];
        ans.val=(1LL*val*lgpow(a.val,phi-1))%MOD;
        return ans;
    }
    int toint()
    {
        int rez=1;
        for(int i=1;i<=NR;i++)
            rez=(1LL*rez*lgpow(F[i],fact[i]))%MOD;
        rez=(1LL*rez*val)%MOD;
        return rez;
    }
};
DA C;
DA tmp;
int rez;
int T,N,K;
const int LEN=10000;
char buffer[LEN];
int ind=LEN-1;
int i32()
{
    int val=0;
    while(buffer[ind]<'0'||buffer[ind]>'9')
        if(++ind>=LEN){
            ind=0;
            fread(buffer,1,LEN,f);
        }
    while(buffer[ind]>='0'&&buffer[ind]<='9'){
        val=val*10+buffer[ind]-'0';
        if(++ind>=LEN){
            ind=0;
            fread(buffer,1,LEN,f);
        }
    }
    return val;
}
int main()
{
    T=i32();
    while(T--)
    {
        N=i32();K=i32();MOD=i32();
        if(N==1){fputs("1\n",g);continue;}
        if(K==1){fprintf(g,"%d\n",(1LL*(N)*(N+1)/2)%MOD);continue;}
        rez=1;
        INIT();
        C=DA();
        for(int i=1;i<=2*K&&i<=N+1;i++)
        {
            tmp=DA(N-i+2);
            C=C*tmp;
            tmp=DA(i);
            C=C/tmp;
            if(i%2==0)
                rez=(rez+C.toint())%MOD;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
