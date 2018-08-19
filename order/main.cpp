#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("order3.in","r");
FILE *g=fopen("order3.out","w");
int N,V[100005];
int Q;
long long nrmod(int sum)///cate siruri au suma sum
{
    if(!sum)return 1;
    return (1LL<<(sum-1));
}
long long ceva(int sum,int elem)///cate siruri mai mici lexicografie exista de suma s daca primul element ar fi elem
{
    return ((1LL<<(elem-1))-1)<<max(0,sum-elem);
}
///iese cu putina mate
long long alcatelea()
{
    int S=0;
    long long P=1;
    for(int i=1;i<=N;i++)S+=V[i];
    for(int i=1;i<S;i++)P+=nrmod(i);
    for(int i=1;i<=N;i++)
    {
        P+=ceva(S,V[i]);
        S-=V[i];
    }
    return P;
}
void care(long long P)
{
    int S=1;
    while(P>nrmod(S))
    {
        P-=nrmod(S);
        S++;
    }
    N=0;
    while(S)
    {
        N++;
        int st=1,dr=1000;
        while(st<dr)
        {
            int mid=(st+dr)>>1;
            if(ceva(S,mid+1)<P)
                st=mid+1;
            else
                dr=mid;
        }
        V[N]=st;
        P-=ceva(S,V[N]);
        S-=V[N];
    }
}
int main()
{
    fscanf(f,"%d",&Q);
    while(Q--)
    {
        int tip;
        fscanf(f,"%d",&tip);
        if(tip==1)
        {
            fscanf(f,"%d",&N);
            for(int i=1;i<=N;i++)fscanf(f,"%d",&V[i]);
            fprintf(g,"%lld\n",alcatelea());
        }
        else
        {
            long long P;
            fscanf(f,"%lld",&P);
            care(P);
            fprintf(g,"%d ",N);
            for(int i=1;i<=N;i++)fprintf(g,"%d ",V[i]);
            fprintf(g,"\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
