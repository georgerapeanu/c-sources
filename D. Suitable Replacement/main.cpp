#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int fr[280];
int fr2[280];
vector<char> V;
int N,M;
char s[1000005];
char t[1000005];
int main()
{
    gets(s+1);N=strlen(s+1);N-=(s[N]=='\n');
    gets(t+1);M=strlen(t+1);M-=(t[M]=='\n');
    for(int i=1;i<=N;i++)fr[s[i]]++;
    int j=1;
    for(int i=1;i<=N;i++)
    {
        if(fr[t[j]])fr[t[j]]--;
        else if(fr['?']){fr['?']--;V.push_back(t[j]);}
        j=j%M+1;
    }
    j=0;
    for(int i=1;i<=N;i++)
    {
        if(s[i]=='?')putc(V[j++],stdout);
        else putc(s[i],stdout);
    }
    return 0;
}
