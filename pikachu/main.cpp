#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
FILE *f=fopen("pikachu.in","r");
FILE *g=fopen("pikachu.out","w");
int V[100005];
multiset <int> A;
multiset<int> B;
multiset<int> ::iterator it;
long long sA,sB;
int N,K;
int elem()
{
    return *A.rbegin();
}
void balance()
{
    while(A.size()>1+B.size())
    {
        B.insert(*A.rbegin());
        sA-=*A.rbegin();
        sB+=*A.rbegin();
        it=A.find(*A.rbegin());
        A.erase(it);
    }
    while(B.size()>=1+A.size())
    {
        A.insert(*B.begin());
        sA+=*B.begin();
        sB-=*B.begin();
        B.erase(B.begin());
    }
}
void ins(int val)
{
    if(val>=(*B.begin()))
    {
        sB+=val;
        B.insert(val);
    }
    else
    {
        sA+=val;
        A.insert(val);
    }
    balance();
}
void del(int val)
{
    if((*A.rbegin())>=val)
    {
        it=A.find(val);
        A.erase(it);
        sA-=val;
    }
    else
    {
        it=B.find(val);
        B.erase(it);
        sB-=val;
    }
    balance();
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    for(int i=0;i<K;i++)
        ins(V[i]);
    long long rez=(1LL<<62);
    for(int i=K;i<=N;i++)
    {
        ins(V[i]);
        del(V[i-K]);
        int nr=elem();
        rez=min(1LL*nr*A.size()-sA+sB-1LL*nr*B.size(),rez);
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
