#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long rad;
long long N,M;
long long A[200005];
struct q
{
    long long st,dr,ind,buck;
    bool operator <(q &other)
    {
        if(buck!=other.buck)
            return buck<other.buck;
        return dr<other.dr;
    }
};
q V[200005];
long long rez[200005];
long long fr[1000005];
long long val;
void add(long long poz)
{
    val+=(2*fr[A[poz]]+1)*A[poz];
    fr[A[poz]]++;
}
void rem(long long poz)
{
    fr[A[poz]]--;
    val-=(2*fr[A[poz]]+1)*A[poz];
}
int main()
{
    long long l=1,r=0;
    scanf("%I64d",&N);
    scanf("%I64d",&M);
    rad=sqrt(N);
    for(int i=1; i<=N; i++)
        scanf("%I64d",&A[i]);
    for(int i=1; i<=M; i++)
    {
        scanf("%I64d",&V[i].st);
        scanf("%I64d",&V[i].dr);
        V[i].ind=i;
        V[i].buck=V[i].st/rad;
    }
    sort(V+1,V+1+M);
    for(int i=1; i<=M; i++)
    {
        while(r<V[i].dr)
        {
            r++;
            add(r);
        }
        while(r>V[i].dr)
        {
            rem(r);
            r--;
        }
        while(l>V[i].st)
        {
            l--;
            add(l);
        }
        while(l<V[i].st)
        {
            rem(l);
            l++;
        }
        rez[V[i].ind]=val;
    }
    for(int i=1; i<=M; i++)
        printf("%I64d\n",rez[i]);
    return 0;
}