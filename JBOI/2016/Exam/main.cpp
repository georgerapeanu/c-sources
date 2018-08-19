#include <iostream>
#include <cstdio>
#include <algorithm>
#define DEG 0
using namespace std;
int frecv[10000005];
long long frecv2[20000005];
int V[3005];
int N,ind=0;
long long rez;
long long C(long long N,long long K)
{
    if(N<K)return 0;
    if(K==1)return N;
    if(K==2)return N*(N-1)/2;
    if(K==3)return N*(N-1)*(N-2)/6;
    return N*(N-1)*(N-2)*(N-3)/24;
}
int main()
{
    if(DEG)
    {
        freopen("in","r",stdin);
        freopen("out","w",stdout);
    }
    cin>>N;
    for(int i=1;i<=N;i++){cin>>V[i];frecv[V[i]]++;}
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)if(V[ind]!=V[i])V[++ind]=V[i];
    N=ind;
    for(int i=1;i<=N;i++)for(int j=i+1;j<=N;j++)frecv2[V[i]+V[j]]+=1LL*frecv[V[i]]*frecv[V[j]];
    for(int i=1;i<=N;i++)
    {
        long long tmp=0;
        if(frecv[V[i]]<2)continue;
        for(int j=1;V[j]*2<=V[i]&&j<i;j++)
        {
            if(V[i]==2*V[j]){rez+=C(frecv[V[i]],2)*C(frecv[V[j]],4)+C(frecv[V[i]],2)*C(frecv[V[j]],2)*tmp;tmp+=C(frecv[V[j]],2);}
            else {rez+=C(frecv[V[i]],2)*C(frecv[V[j]],2)*C(frecv[V[i]-V[j]],2)+C(frecv[V[i]],2)*C(frecv[V[j]],1)*C(frecv[V[i]-V[j]],1)*tmp;tmp+=C(frecv[V[j]],1)*C(frecv[V[i]-V[j]],1);}
        }
        if(frecv[V[i]]<3)continue;
        tmp=0;
        for(int j=1;j<i;j++)
        {
            long long realfr=frecv2[V[i]-V[j]];
            if(V[i]-V[j]==2*V[j]);
            else if(V[i]-2*V[j]>=0) realfr-=C(frecv[V[j]],1)*C(frecv[V[i]-2*V[j]],1);
            tmp+=C(frecv[V[i]],3)*C(frecv[V[j]],1)*realfr;///daca nu fac asta numar de 3 ori solutii
            if(V[i]==3*V[j])rez+=C(frecv[V[i]],3)*C(frecv[V[j]],3);
            else if(V[i]-2*V[j]>=0)rez+=C(frecv[V[i]],3)*C(frecv[V[j]],2)*C(frecv[V[i]-2*V[j]],1);
        }
        rez+=tmp/3;
    }
    cout<<rez;
    return 0;
}
