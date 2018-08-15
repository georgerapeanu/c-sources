#include <cstdio>
#include <cstring>
using namespace std;
char S[105];
char T[105];
int N,M;
int K,i;
int main()
{
    gets(S+1);
    gets(T+1);
    scanf("%d",&K);
    N=strlen(S+1);
    M=strlen(T+1);
    i=1;
    while(S[i]==T[i]&&i<=N&&i<=M)
    {
        i++;
    }
    i--;
    if(N-i+M-i<=K&&(K>=N+M||K%2==(N+M)%2))
        puts("Yes");
    else
        puts("No");
    return 0;
}
