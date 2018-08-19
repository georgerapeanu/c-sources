#include <iostream>
#include <cstdio>
#define BASE 1000000
#define LEN 10000
using namespace std;
long long D[10005][2][LEN];
int N,K;
void  shl(long long V[])
{
    for(int i=1;i<V[0];i++)
        V[i]=V[i+1];
    V[0]--;
}
void shr(long long V[])
{
    for(int i=V[0]+1;i>1;i--)
    {
        V[i]=V[i-1];
    }
    V[1]=0;
    V[0]++;
}
void cpy(long long A[],long long B[])
{
    for(int i=0;i<=B[0];i++)
        A[i]=B[i];
}
void add(long long A[],long long B[])
{
    while(A[0]<B[0])
        shr(A);
    while(B[0]<A[0])
        shr(B);
    for(int i=A[0];i>1;i--)
    {
        A[i]+=B[i];
        A[i-1]+=A[i]/BASE;
        A[i]%=BASE;
    }
    A[1]+=B[1];
    while(A[1]>BASE)
    {
        shr(A);
        A[1]=A[2]/BASE;
        A[2]%=BASE;
    }
}
void inmultire(long long A[],long long S)
{
    for(int i=1;i<=A[0];i++)
            A[i]=A[i]*S;
    for(int i=A[0];i>1;i--)
    {
        A[i-1]+=A[i]/BASE;
        A[i]%=BASE;
    }
    while(A[1]>BASE)
    {
        shr(A);
        A[1]=A[2]/BASE;
        A[2]%=BASE;
    }
}
int main()
{
    freopen("temp.in","r",stdin);
    cin>>N>>K;
    freopen("temp.out","w",stdout);
    D[0][0][0]=D[0][0][1]=1;
    for(int i=1;i<=N;i++)
    {
       cpy(D[i][0],D[i-1][1]);
       cpy(D[i][1],D[i-1][0]);
       add(D[i][1],D[i-1][1]);
       inmultire(D[i][1],K-1);
    }
    add(D[N][0],D[N][1]);
    for(int i=1;i<=D[N][0][0];i++)
    {
        if(i!=1)
        {
            if(D[N][0][i]>=100000)
                ;
            else if(D[N][0][i]>=10000)
                cout<<"0";
            else if(D[N][0][i]>=1000)
                cout<<"00";
            else if(D[N][0][i]>=100)
                cout<<"000";
            else if(D[N][0][i]>=10)
                cout<<"0000";
        }
        cout<<D[N][0][i];
    }
    return 0;
}
