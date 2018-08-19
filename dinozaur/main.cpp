#include <cstdio>
#include <unordered_map>
#include <cstring>
using namespace std;
FILE *f=fopen("dinozaur.in","r");
FILE *g=fopen("dinozaur.out","w");
unordered_map <char,int> M;
int i,N;
char S[10005];
bool ok;
int main()
{
    fgets(S,10005,f);
    N=strlen(S);
    for(i=1;i<=N&&!ok;i++)
    {
        M[S[i]]++;
        if(M[S[i]]==2)
            ok=1;
    }
    fprintf(g,"%d",ok);
    fclose(f);
    fclose(g);
    return 0;
}
