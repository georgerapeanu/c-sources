#include <cstdio>
using namespace std;
int AIB[1000005];
int val;
int N;
long long rez;
void u(int pos,int val)
{
    for(;pos<=N;pos+=(-pos)&pos)AIB[pos]+=val;
}
int q(int pos)
{
    int rez=0;
    for(;pos;pos-=(-pos)&pos)rez+=AIB[pos];
    return rez;
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&val);
        rez+=q(val);
        u(val,1);
    }
    printf("%lld",((1LL*N*(N-1))>>1)-rez);
    return 0;
}
