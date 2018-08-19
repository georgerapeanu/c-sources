#include <cstdio>
#include <cstring>
#define MOD 1000000007
using namespace std;
long long S[30];
char C[100005];
long long i,j;
long long T,N;
long long A[100005];
long long B[100005];
int main()
{
    scanf("%lld\n",&T);
    while(T)
    {
        gets(C+1);
        N=strlen(C+1);
        for(i=0;i<30;i++)
            S[i]=0;
        A[0]=1;
        B[0]=0;
        for(i=1;i<=N;i++)
        {
            B[i]=(A[i-1]+B[i-1])%MOD;
            A[i]=(B[i]-S[C[i]-'A'])%MOD;
            if(A[i]<0)
                A[i]+=MOD;
            S[C[i]-'A']=(S[C[i]-'A']+A[i])%MOD;
        }
        printf("%lld\n",(A[N]+B[N])%MOD);
        T--;
    }
    return 0;
}
