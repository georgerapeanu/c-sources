#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;
FILE *f=fopen("superbec.in","r");
FILE *g=fopen("superbec.out","w");
int N,M,T;
int st[256],dr[256];
int S[31];
int D[31];
char C[100005];
int a[]={1,2,2,3,3,5,5,5,5};
int b[]={0,0,1,1,2,0,2,3,4};
int V[11];
int val[31];
int rez;
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int Co(int N,int K)
{
    K=max(K,N-K);
    int rez=1,imp=1;
    for(int i=K+1;i<=N;i++) rez=(1LL*rez*i)%MOD;
    for(int i=2;i<=N-K;i++) imp=(1LL*imp*i)%MOD;
    return (1LL*rez*lgpow(imp,MOD-2))%MOD;
}
void btr(int pas,int suma)
{
    if(pas>9)
    {
        if((M-suma)%3!=0) return ;
        for(int i=1;i<=N&&i<=30;i++)
        {
            val[i]=0;
            for(int j=0;j<9;j++)
                if(i%a[j]==b[j])
                {
                    val[i]+=V[j+1];
                    if(val[i]>=3) val[i]-=3;
                }
            if(!(S[i]<=val[i]&&val[i]<=D[i])) return ;
        }
        rez+=Co((M-suma)/3+8,8);
        if(rez>=MOD) rez-=MOD;
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            if(suma+i>M) break;
            V[pas]=i;
            btr(pas+1,suma+i);
        }
    }
}
int main()
{
    st['0']=dr['0']=0;
    st['1']=dr['1']=1;
    st['2']=dr['2']=2;
    st['a']=0;dr['a']=1;
    st['b']=1;dr['b']=2;
    st['?']=0;dr['?']=2;
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        fscanf(f,"%d %d\n",&N,&M);
        fgets(C+1,100005,f);
        bool ok=1;
        for(int i=1;i<=N;i++)
        {
            if(i<=30) S[i]=st[C[i]],D[i]=dr[C[i]];
            else S[(i-1)%30+1]=max(st[C[i]],S[(i-1)%30+1]),D[(i-1)%30+1]=min(D[(i-1)%30+1],dr[C[i]]);
            if(S[(i-1)%30+1]>D[(i-1)%30+1]) ok=0;
        }
        if(ok==0){fputs("0\n",g);continue;}
        rez=0;
        btr(1,0);
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
