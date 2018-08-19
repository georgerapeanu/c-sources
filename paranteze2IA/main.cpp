#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
FILE *f=fopen("paranteze2.in","r");
FILE *g=fopen("paranteze2.out","w");
char C[1000005];
int dp[1000005];
int N;
long long rez;
stack<int> P;
stack<char> S;
int main()
{
    fgets(C+1,1000005,f);
    N=strlen(C+1);
    N-=(C[N]=='\n');
    for(int i=1;i<=N;i++)
    {
        bool ok=1;
        if(C[i]==')')
        {
            if(S.empty()||(S.top()==')'))
                ;
            else
                {ok=0;dp[i]=dp[P.top()-1]+1;P.pop();S.pop();}
        }
        if(ok)
        {
            S.push(C[i]);
            P.push(i);
        }
        rez+=dp[i];
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
