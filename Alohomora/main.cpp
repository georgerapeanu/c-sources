#include <cstdio>
#include <algorithm>
#include <set>
#define LL long long
#define r first
#define ind second
using namespace std;
FILE *f=fopen("alohomora.in","r");
FILE *g=fopen("alohomora.out","w");
typedef pair<int,int> pii;
pii S[100005];
multiset<pii> C;
multiset<pii>::iterator it;
pii tmp;
int N,T,M,K;
int chei;
int nr;
LL lgpow(LL b,LL e)
{
    if(e<0)
        return 1;
    LL p=1;
    while(e)
    {
        if(e&1)
        {
            if(p*b>chei)
                return 1000001;
            p=p*b;
        }
        b*=b;
        e>>=1;
        if(b>chei&&e)
            return 1000001;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        fscanf(f,"%d%d%d",&N,&M,&K);
        C.clear();
        nr=chei=0;
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%d %d",&tmp.r,&tmp.ind);
            C.insert(tmp);
        }
        for(int i=1;i<=M;i++)
        {
            fscanf(f,"%d %d",&S[i].r,&S[i].ind);
            it=C.lower_bound(S[i]);
            if(it!=C.end()&&it->r==S[i].r&&it->ind==S[i].ind)
            {
                C.erase(it);
                i--;
                M--;
            }
        }
        sort(S+1,S+1+M);
        int j=1;
        int rang=0;
        for(auto it:C)
        {
            while(chei&&j<=M&&rang==S[j].r)
                j++,chei--;
            if(it.r==rang)
                nr++;
            else
            {
                chei+=nr;
                nr=1;
                chei/=K;
                rang++;
            }
            while(it.r>=S[j].r&&chei/lgpow(K,S[j].r-rang)&&j<=M)
            {
                chei/=lgpow(K,S[j].r-rang);
                rang=max(rang,S[j].r);
                chei--;
                j++;
            }
            if(it.r>S[j].r)
                nr--,j++;
            chei/=lgpow(K,it.r-rang);
            rang=it.r;
        }
        chei=(chei+nr)/K;
        rang++;
        while(chei/lgpow(K,S[j].r-rang)&&j<=M)
        {
            chei/=lgpow(K,S[j].r-rang);
            rang=max(rang,S[j].r);
            chei--;
            j++;
        }
        if(j>M)
            fputs("1\n",g);
        else
            fputs("0\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
