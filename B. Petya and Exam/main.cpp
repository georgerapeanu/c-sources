#include <cstdio>
#include <cstring>
using namespace std;
char S[100005];
char T[100005];
bool good[280];
int N,M;
int Q;
bool are;
int main()
{
    fgets(T+1,100005,stdin);N=strlen(T+1);N-=(T[N]=='\n');
    for(int i=1;i<=N;i++)good[T[i]]=1;
    fgets(T+1,100005,stdin);N=strlen(T+1);N-=(T[N]=='\n');for(int i=1;i<=N;i++)are|=(T[i]=='*');
    scanf("%d\n",&Q);
    while(Q--)
    {
        fgets(S+1,100005,stdin);M=strlen(S+1);M-=(S[M]=='\n');
        if(M<N-are){printf("NO\n");continue;}
        int st=1,dr=1;
        while(st<=N)
        {
            if(T[st]=='?')
            {
                if(!good[S[st]])break;
            }
            else if(T[st]!=S[st])
                break;
            st++;
        }
        if(st>N){if(N!=M)printf("NO\n");else printf("YES\n");continue;}
        while(dr<=N)
        {
            if(T[N-dr+1]=='?')
            {
                if(!good[S[M-dr+1]])break;
            }
            else if(T[N-dr+1]!=S[M-dr+1])break;
            dr++;
        }
        if(T[N-dr+1]!='*'||T[st]!='*'){printf("NO\n");continue;}
        bool ok=1;
        for(int i=st;i<=M-dr+1;i++)if(good[S[i]])ok=0;
        if(ok)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
