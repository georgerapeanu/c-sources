#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int rad;
int N,M;
int A[30005];
struct q
{
    int st,dr,ind,buck;
    bool operator <(q &other)
    {
        if(buck!=other.buck)
            return buck<other.buck;
        return dr<other.dr;
    }
};
q V[200005];
int rez[200005];
int fr[1000005];
int val;
void add(int poz)
{
    fr[A[poz]]++;
    if(fr[A[poz]]==1)
        val++;
}
void rem(int poz)
{
    fr[A[poz]]--;
    if(fr[A[poz]]==0)
        val--;
}
int main()
{
    int l=1,r=0;
    scanf("%d",&N);
    rad=sqrt(N);
    for(int i=1;i<=N;i++)
        scanf("%d",&A[i]);
    scanf("%d",&M);
    for(int i=1;i<=M;i++)
    {
        scanf("%d",&V[i].st);
        scanf("%d",&V[i].dr);
        V[i].ind=i;
        V[i].buck=V[i].st/rad;
    }
    sort(V+1,V+1+M);
    for(int i=1;i<=M;i++)
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
    for(int i=1;i<=M;i++)
        printf("%d\n",rez[i]);
    return 0;
}
