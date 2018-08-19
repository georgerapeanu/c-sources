#include <cstdio>
#include <algorithm>
using namespace std;
int N,rez;
long long S[200005];
long long m[200005];
long long M[200005];
int main()
{
    scanf("%d",&N);
    m[0]=m[N+1]=M[0]=M[N+1]=1LL<<62;
    for(int i=1;i<=N;i++){scanf("%I64d",&S[i]);S[i]+=S[i-1];m[i]=min(S[i],m[i-1]);}
    for(int i=N;i;i--)M[i]=min(M[i+1],S[i]);
    for(int i=1;i<=N;i++)
    {
        if(M[i]-S[i-1]>=0&&S[N]-S[i-1]+m[i-1]>=0)
            rez++;
    }
    printf("%d",rez);
    return 0;
}
