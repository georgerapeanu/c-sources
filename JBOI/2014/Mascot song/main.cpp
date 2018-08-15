#include <cstdio>
using namespace std;
int N,Q;
int A[400005];
int V[400005];
void u(int pos,int val)
{
    for(;pos<=2*N;pos+=(-pos)&pos)
    {
        V[pos]+=val;
    }
}
int q(int pos)
{
    int sum=0;
    for(;pos;pos-=(-pos)&pos)
        sum+=V[pos];
    return sum;
}
int st=1;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
    }
    for(int i=N+1;i<=2*N;i++)
    {
        A[i]=A[i-N];
    }
    for(int i=2;i<=2*N;i++)
    {
        if(A[i]<=A[i-1])u(i,1);
    }
    scanf("%d",&Q);
    while(Q--)
    {
        int t,x,y;
        scanf("%d",&t);
        if(t==2)
        {
            scanf("%d",&x);
            st+=x;
            if(st>N)st-=N;
        }
        else
        {
            scanf("%d %d",&x,&y);
            x=st+x-1;if(x>N)x-=N;
            if(A[x]<=A[x-1])u(x,-1);
            if(A[x+1]<=A[x])u(x+1,-1);
            A[x]=y;
            if(A[x]<=A[x-1])u(x,1);
            if(A[x+1]<=A[x])u(x+1,1);
            x+=N;
            if(A[x]<=A[x-1])u(x,-1);
            if(A[x+1]<=A[x])u(x+1,-1);
            A[x]=y;
            if(A[x]<=A[x-1])u(x,1);
            if(A[x+1]<=A[x])u(x+1,1);
        }
        printf("%d\n",q(st+N-1)-q(st)+1);
    }
    return 0;
}
